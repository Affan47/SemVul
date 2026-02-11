manifest_file_seek_base(Manifest *p, const char *zName){
  int lwr, upr;
  int c;
  int i;
  lwr = 0;
  upr = p->nFile - 1;
  if( p->iFile>=lwr && p->iFile<upr ){
    c = fossil_strcmp(p->aFile[p->iFile+1].zName, zName);
    if( c==0 ){
      return &p->aFile[++p->iFile];
    }else if( c>0 ){
      upr = p->iFile;
    }else{
      lwr = p->iFile+1;
    }
  }
  while( lwr<=upr ){
    i = (lwr+upr)/2;
    c = fossil_strcmp(p->aFile[i].zName, zName);
    if( c<0 ){
      lwr = i+1;
    }else if( c>0 ){
      upr = i-1;
    }else{
      p->iFile = i;
      return &p->aFile[i];
    }
  }
  return 0;
}
