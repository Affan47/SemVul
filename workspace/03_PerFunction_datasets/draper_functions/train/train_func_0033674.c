cmdh_change_toggle(struct command *cmd)
{
  int toggle = cmd->arg[0][0];
  int ret;

  ret = anthy_input_edit_toggle_config(config, toggle);

  if (ret != 0) {
    send_error();
    return;
  }
  anthy_input_change_config(config);
  send_ok();
}
