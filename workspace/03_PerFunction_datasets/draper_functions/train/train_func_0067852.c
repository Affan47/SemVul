append_val(char * orig, char const * val){
  char *z;
  if( !orig ){
    z = sqliteStrDup( val );
  } else{
    z = 0;
    sqliteSetString(&z, orig, val, (char*)0);
    sqliteFree( orig );
  }
  return z;
}
