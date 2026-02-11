cmd_init(struct ctrl_command *cmd)
{
  if (in_state.active || out_state.active)
    send_error("CMD_INIT sent twice!");

  in_state.active = 1;
  out_state.active = 1;
  CONTROL_R.read_cb = read_ctrl;
  CONTROL_W.write_cb = NULL;
  LOCAL_R.read_cb = read_data;
  LOCAL_W.write_cb = NULL;
  REMOTE_R.read_cb = read_net;
  REMOTE_W.write_cb = NULL;
}
