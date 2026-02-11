ShutdownProtobufLibrary() {
  internal::InitShutdownFunctionsOnce();


  if (internal::shutdown_functions == NULL) return;

  for (int i = 0; i < internal::shutdown_functions->size(); i++) {
    internal::shutdown_functions->at(i)();
  }
  delete internal::shutdown_functions;
  internal::shutdown_functions = NULL;
  delete internal::shutdown_functions_mutex;
  internal::shutdown_functions_mutex = NULL;
}
