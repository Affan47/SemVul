register_commands_ctrl(void)
{
  (*cmd_map_repp)["ctrl-add"] = ec_ctrl_add;
  (*cmd_map_repp)["ctrl-describe"] = ec_ctrl_describe;
  (*cmd_map_repp)["ctrl-remove"] = ec_ctrl_remove;
  (*cmd_map_repp)["ctrl-list"] = ec_ctrl_list;
  (*cmd_map_repp)["ctrl-select"] = ec_ctrl_select;
  (*cmd_map_repp)["ctrl-index-select"] = ec_ctrl_select;
  (*cmd_map_repp)["ctrl-iselect"] = ec_ctrl_select;
  (*cmd_map_repp)["ctrl-register"] = ec_ctrl_register;
  (*cmd_map_repp)["ctrl-selected"] = ec_ctrl_selected;
  (*cmd_map_repp)["ctrl-status"] = ec_ctrl_status;
  (*cmd_map_repp)["ctrl-get-target"] = ec_ctrl_get_target;
}
