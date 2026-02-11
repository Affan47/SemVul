prefix_uli(char *data, size_t size){
  size_t i = 0;
  if( i<size && data[i]==' ') i++;
  if( i<size && data[i]==' ') i++;
  if( i<size && data[i]==' ') i++;
  if( i+1>=size
   || (data[i]!='*' && data[i]!='+' && data[i]!='-')
   || (data[i+1]!=' ' && data[i+1]!='\t')
  ){
    return 0;
  }
  i = i+2;
  while( i<size && (data[i]==' ' || data[i]=='\t') ){ i++; }
  return i;
}
