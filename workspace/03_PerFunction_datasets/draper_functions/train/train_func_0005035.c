initializeExternalFunctions() {
  sys::ScopedLock Writer(*FunctionsLock);
  FuncNames["lle_X_atexit"]       = lle_X_atexit;
  FuncNames["lle_X_exit"]         = lle_X_exit;
  FuncNames["lle_X_abort"]        = lle_X_abort;

  FuncNames["lle_X_printf"]       = lle_X_printf;
  FuncNames["lle_X_sprintf"]      = lle_X_sprintf;
  FuncNames["lle_X_sscanf"]       = lle_X_sscanf;
  FuncNames["lle_X_scanf"]        = lle_X_scanf;
  FuncNames["lle_X_fprintf"]      = lle_X_fprintf;
}
