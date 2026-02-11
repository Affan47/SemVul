ifnullFunc(sqlite_func *context, int argc, const char **argv){
  int i;
  for(i=0; i<argc; i++){
    if( argv[i] ){
      sqlite_set_result_string(context, argv[i], -1);
      break;
    }
  }
}
