HandleData(const char* aBuf, unsigned int aLen)
{
  nsSMState codingState;
  int j;
  uint i, weight_BOM, counts[5];
  static bool disableUTF16LE = false;
  static bool disableUTF16BE = false;
  double weight_zero;

  if (mActiveSM <= 0) {
      mState = eNotMe;
      return mState;
  }

  if (! (disableUTF16LE || disableUTF16BE)) {
    if (aLen%2 != 0) {
            disableUTF16LE = true;
            disableUTF16BE = true;
    }
    weight_BOM = (uint)(sqrt((double)aLen) + aLen/10.0);
    for (uint i = 0; i < 5; i++)
        qCount(aBuf, aBuf+aLen, char(i), counts[i]);
    weight_zero = (2.0*(counts[0] + counts[1] + counts[2] + counts[3] + counts[4]) + weight_BOM)/aLen;
    if (weight_zero < log(1.4142)) {
        disableUTF16LE = true;
        disableUTF16BE = true;
    }
    if (4 >= aBuf[1] && aBuf[1] >= 0 && isprint(aBuf[0]))
        disableUTF16BE = true;
    else
        disableUTF16LE = true;
    if (disableUTF16BE)
      mActiveSM--;
    if (disableUTF16LE) {
      nsCodingStateMachine* t;
      t = mCodingSM[1];
      mCodingSM[1] = mCodingSM[2];
      mCodingSM[2] = t;
      mActiveSM--;
    }
  }

  for (i = 0; i < aLen; ++i) {
    for (j = mActiveSM-1; j>= 0; --j)
    {

      codingState = mCodingSM[j]->NextState(aBuf[i]);
      if (codingState == eError)
      {

        mActiveSM--;
        if (mActiveSM == 0)
        {
          mState = eNotMe;
          return mState;
        }
        else if (j != (int)mActiveSM)
        {
          nsCodingStateMachine* t;
          t = mCodingSM[mActiveSM];
          mCodingSM[mActiveSM] = mCodingSM[j];
          mCodingSM[j] = t;
        }
      }
      else if (codingState == eItsMe)
      {
        mState = eFoundIt;
        mDetectedCharset = mCodingSM[j]->GetCodingStateMachine();
        return mState;
      } else if (mState == eDetecting)
          mDetectedCharset = mCodingSM[j]->GetCodingStateMachine();;
    }
  }
  return mState;
}
