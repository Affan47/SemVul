is_mail_autolink(char *data, size_t size){
  size_t i = 0, nb = 0;

  while( i<size && (data[i]=='-'
   || data[i]=='.'
   || data[i]=='_'
   || data[i]=='@'
   || (data[i]>='a' && data[i]<='z')
   || (data[i]>='A' && data[i]<='Z')
   || (data[i]>='0' && data[i]<='9'))
  ){
    if( data[i]=='@' ) nb++;
    i++;
  }
  if( i>=size || data[i]!='>' || nb!=1 ) return 0;
  return i+1;
}
