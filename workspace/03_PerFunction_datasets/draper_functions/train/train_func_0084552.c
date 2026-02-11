GACheckDecoding(unsigned int& nbits)
{
  if((int)nbits >= _GA_MAX_BITS){
    sprintf(_gaerrbuf1,"string is %d bits, max is %d", nbits, _GA_MAX_BITS-1);
    GAErr(GA_LOC, "GACheckDecoding", gaErrBinStrTooLong, _gaerrbuf1);
    nbits = _GA_MAX_BITS-1;
    return 1;
  }
  return 0;
}
