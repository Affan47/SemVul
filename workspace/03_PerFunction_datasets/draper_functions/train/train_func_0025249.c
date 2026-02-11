setColType(const char *array, bool copyIn)
{
  if (owned_.colType)
    delete [] colType_;
  if (copyIn) {
    owned_.colType=1;
    colType_ = CoinCopyOfArray(array,numCols_);
  } else {
    owned_.colType=0;
    colType_ = array;
  }
  int i;
  numIntegers_=0;
  for (i=0;i<numCols_;i++) {
    if (colType_[i]=='B'||colType_[i]=='I')
      numIntegers_++;
  }
}
