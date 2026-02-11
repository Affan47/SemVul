thEndOfLine(const char *zInput, int nInput){
  int i;
  for(i=0; i<nInput && zInput[i]!='\n' && th_isspace(zInput[i]); i++);
  return ((i==nInput || zInput[i]=='\n')?1:0);
}
