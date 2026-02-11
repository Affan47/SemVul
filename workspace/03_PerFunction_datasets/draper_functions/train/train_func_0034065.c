LSL_loadPardisoLib(const char* libname, char* msgbuf, int msglen) {

  if (libname) {
    Pardiso_handle=LSL_loadLib(libname, msgbuf, msglen);
  } else {
    Pardiso_handle=LSL_loadLib(PARDISOLIBNAME, msgbuf, msglen);
  }
  if (Pardiso_handle==NULL)
    return 1;


  if(LSL_loadSym(Pardiso_handle, "pardiso_ipopt_newinterface", msgbuf, msglen) != NULL) {
     func_new_pardisoinit=(pardisoinit_new_t)LSL_loadSym(Pardiso_handle, "pardisoinit", msgbuf, msglen);
     if (func_new_pardisoinit == NULL) return 1;

     func_new_pardiso=(pardiso_new_t)LSL_loadSym(Pardiso_handle, "pardiso", msgbuf, msglen);
     if (func_new_pardiso == NULL) return 1;

  } else {
     func_pardisoinit=(pardisoinit_old_t)LSL_loadSym(Pardiso_handle, "pardisoinit", msgbuf, msglen);
     if (func_pardisoinit == NULL) return 1;

     func_pardiso=(pardiso_old_t)LSL_loadSym(Pardiso_handle, "pardiso", msgbuf, msglen);
     if (func_pardiso == NULL) return 1;

     func_new_pardisoinit = wrap_old_pardisoinit;
     func_new_pardiso = wrap_old_pardiso;
  }


  pardiso_is_parallel = LSL_loadSym(Pardiso_handle, "pardiso_exist_parallel", msgbuf, msglen) != NULL;

  return 0;
}
