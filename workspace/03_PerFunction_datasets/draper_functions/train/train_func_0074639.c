assignBasisStatus(int ns, int na, char*& sStat,
				     char*& aStat) {

  int nintS = (ns+15) >> 4;
  int nintA = (na+15) >> 4;
  int size = nintS+nintA;
  if (size) {
    if (size>maxSize_) {
      delete[] structuralStatus_;
      maxSize_ = size+10;
      structuralStatus_ = new char[4*maxSize_];
    }
    CoinMemcpyN( sStat,(4*nintS), structuralStatus_);
    artificialStatus_ = structuralStatus_+4*nintS;
    CoinMemcpyN( aStat,(4*nintA), artificialStatus_);
  } else {
    artificialStatus_ = NULL;
  }
  numStructural_ = ns;
  numArtificial_ = na;
  delete [] sStat;
  delete [] aStat;
  sStat = NULL;
  aStat = NULL;
}
