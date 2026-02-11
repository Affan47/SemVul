uv__dlerror(uv_lib_t* lib) {
  char* errmsg;

  if (lib->errmsg)
    free(lib->errmsg);

  errmsg = dlerror();

  if (errmsg) {
    lib->errmsg = strdup(errmsg);
    return -1;
  }
  else {
    lib->errmsg = NULL;
    return 0;
  }
}
