sys_module_init(global_t *global) {
  apr_status_t status;
  if ((status = module_command_new(global, "THREAD", "_GET_NUMBER",
	                           "<var>",
	                           "Stores the number of current thread",
	                           block_THREAD_GET_NUMBER)) != APR_SUCCESS) {
    return status;
  }
  if ((status = module_command_new(global, "PROC", "_LOCK",
	                           "",
	                           "Draws lock, for CLIENT/SERVER synchronization",
	                           block_PROC_LOCK)) != APR_SUCCESS) {
    return status;
  }
  if ((status = module_command_new(global, "PROC", "_UNLOCK",
	                           "",
	                           "Release lock, for CLIENT/SERVER synchronization",
	                           block_PROC_UNLOCK)) != APR_SUCCESS) {
    return status;
  }
  if ((status = module_command_new(global, "PROC", "_GET_PID",
	                           "<var>",
	                           "Store PID into a <var>",
	                           block_PROC_GET_PID)) != APR_SUCCESS) {
    return status;
  }
  if ((status = module_command_new(global, "PROC", "_DETACH",
	                           "",
	                           "Detach process to background for daemonize",
	                           block_PROC_DETACH)) != APR_SUCCESS) {
    return status;
  }
  if ((status = module_command_new(global, "SYS", "_SLEEP",
	                           "<miliseconds>",
				   "Sleep for defined amount of time",
	                           block_SYS_SLEEP)) != APR_SUCCESS) {
    return status;
  }

  return APR_SUCCESS;
}
