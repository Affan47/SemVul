register_commands_copp(void)
{
  (*cmd_map_repp)["copp-list"] = ec_copp_list;
  (*cmd_map_repp)["copp-select"] = ec_copp_select;
  (*cmd_map_repp)["copp-index-select"] = ec_copp_select;
  (*cmd_map_repp)["copp-iselect"] = ec_copp_select;
  (*cmd_map_repp)["copp-selected"] = ec_copp_selected;
  (*cmd_map_repp)["copp-set"] = ec_copp_set;
  (*cmd_map_repp)["copp-get"] = ec_copp_get;
}
