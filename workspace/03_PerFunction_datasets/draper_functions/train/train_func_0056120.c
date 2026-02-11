resize (int newNumberRows, int newNumberColumns)
{
  int i , nCharNewS, nCharOldS, nCharNewA, nCharOldA;
  if (newNumberRows!=numArtificial_||newNumberColumns!=numStructural_) {
    nCharOldS  = 4*((numStructural_+15)>>4);
    int nIntS  = (newNumberColumns+15)>>4;
    nCharNewS  = 4*nIntS;
    nCharOldA  = 4*((numArtificial_+15)>>4);
    int nIntA  = (newNumberRows+15)>>4;
    nCharNewA  = 4*nIntA;
    int size = nIntS+nIntA;

    if (newNumberColumns>numStructural_||
	size>maxSize_) {
      if (size>maxSize_)
	maxSize_ = size+10;
      char * array = new char[4*maxSize_];

      memset(array,0,4*maxSize_*sizeof(char));
      CoinMemcpyN(structuralStatus_,(nCharOldS>nCharNewS)?nCharNewS:nCharOldS,array);
      CoinMemcpyN(artificialStatus_,	     (nCharOldA>nCharNewA)?nCharNewA:nCharOldA,
                   array+nCharNewS);
      delete [] structuralStatus_;
      structuralStatus_ = array;
      artificialStatus_ = array+nCharNewS;
      for (i=numStructural_;i<newNumberColumns;i++)
	setStructStatus(i, atLowerBound);
      for (i=numArtificial_;i<newNumberRows;i++)
	setArtifStatus(i, basic);
    } else {

      if (newNumberColumns!=numStructural_) {
	memmove(structuralStatus_+nCharNewS,artificialStatus_,
		(nCharOldA>nCharNewA)?nCharNewA:nCharOldA);
	artificialStatus_ = structuralStatus_+4*nIntS;
      }
      for (i=numArtificial_;i<newNumberRows;i++)
	setArtifStatus(i, basic);
    }
    numStructural_ = newNumberColumns;
    numArtificial_ = newNumberRows;
  }
}
