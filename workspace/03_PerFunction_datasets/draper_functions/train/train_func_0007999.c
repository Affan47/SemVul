is_valid_uuid(const char *z){
  int n = strlen(z);
  if( n<4 || n>UUID_SIZE ) return 0;
  if( !validate16(z, n) ) return 0;
  return 1;
}
