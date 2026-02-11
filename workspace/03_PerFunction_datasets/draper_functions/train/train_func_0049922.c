start_standalone_factor_thread(void* arg) {
  factor_vm* newvm = new_factor_vm();
  startargs* args = (startargs*)arg;
  int argc = args->argc;
  vm_char** argv = args->argv;
  delete args;
  newvm->start_standalone_factor(argc, argv);
  return 0;
}
