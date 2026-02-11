Get_param_log_impl(int index, int handle) {
  int           command[1];
  static char** command_params = NULL;

  command[0] = REG_STR_EMIT_PARAM_LOG;


  if(!command_params) command_params = Alloc_string_array(32, 1);
  sprintf(command_params[0], "%d", handle);

  return Emit_control(Sim_table.sim[index].handle,
		      1,
		      command,
		      command_params);
}
