read(STD_ISTREAM & is)
{
  static char c;
  unsigned int i=0, j=0;
  while(!is.fail() && !is.eof() && j < ny) {
    is >> c;
    if(isdigit(c)){
      gene(i, j, ((c == '0') ? 0 : 1));
      if(++i >= nx){
	i=0;
	j++;
      }
    }
  }

  _evaluated = gaFalse;

  if(is.eof() &&
     ((j < ny) ||
      (i < nx && i != 0))){
    GAErr(GA_LOC, className(), "read", gaErrUnexpectedEOF);
    is.clear(STD_IOS_BADBIT | is.rdstate());
    return 1;
  }

  return 0;
}
