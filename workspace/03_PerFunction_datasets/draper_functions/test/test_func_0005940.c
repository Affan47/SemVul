add_param_list(char *z, int terminator){
  int isQP = terminator=='&';
  while( *z ){
    char *zName;
    char *zValue;
    while( fossil_isspace(*z) ){ z++; }
    zName = z;
    while( *z && *z!='=' && *z!=terminator ){ z++; }
    if( *z=='=' ){
      *z = 0;
      z++;
      zValue = z;
      while( *z && *z!=terminator ){ z++; }
      if( *z ){
        *z = 0;
        z++;
      }
      dehttpize(zValue);
    }else{
      if( *z ){ *z++ = 0; }
      zValue = "";
    }
    if( fossil_islower(zName[0]) ){
      cgi_set_parameter_nocopy(zName, zValue, isQP);
    }
#ifdef FOSSIL_ENABLE_JSON
    json_setenv( zName, cson_value_new_string(zValue,strlen(zValue)) );
#endif
  }
}
