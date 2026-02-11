deleteColumns(int number, const int * which)
{
  int i ;
  char * deleted = new char[numStructural_];
  int numberDeleted=0;
  memset(deleted,0,numStructural_*sizeof(char));
  for (i=0;i<number;i++) {
    int j = which[i];
    if (j>=0&&j<numStructural_&&!deleted[j]) {
      numberDeleted++;
      deleted[j]=1;
    }
  }
  int nCharNewS  = 4*((numStructural_-numberDeleted+15)>>4);
  int nCharNewA  = 4*((numArtificial_+15)>>4);
  char * array = new char[4*maxSize_];
# ifdef ZEROFAULT
  memset(array,0,(4*maxSize_*sizeof(char))) ;
# endif
  CoinMemcpyN(artificialStatus_,nCharNewA,array+nCharNewS);
  int put=0;
# ifdef COIN_DEBUG
  int numberBasic=0;
# endif
  for (i=0;i<numStructural_;i++) {
    Status status = getStructStatus(i);
    if (!deleted[i]) {
      setStatus(array,put,status) ;
      put++; }
#   ifdef COIN_DEBUG
    else
    if (status==CoinWarmStartBasis::basic)
    { numberBasic++ ; }
#   endif
  }
  delete [] structuralStatus_;
  structuralStatus_ = array;
  artificialStatus_ = structuralStatus_ + nCharNewS;
  delete [] deleted;
  numStructural_ -= numberDeleted;
#ifdef COIN_DEBUG
  if (numberBasic)
    std::cout<<numberBasic<<" basic structurals deleted"<<std::endl;
#endif
}
