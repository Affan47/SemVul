Reset(void)
{
  mState = eDetecting;
  for (unsigned int i = 0; i < NUM_OF_UNICODE_CHARSETS; i++)
    mCodingSM[i]->Reset();
  mActiveSM = NUM_OF_UNICODE_CHARSETS;
  mDetectedCharset = "UTF-8";
}
