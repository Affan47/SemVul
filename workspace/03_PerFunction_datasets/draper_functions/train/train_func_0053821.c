gen_def_assigns (gimple_stmt_iterator *gsi, struct switch_conv_info *info)
{
  int i;
  gimple assign = NULL;

  for (i = 0; i < info->phi_count; i++)
    {
      tree name = copy_ssa_name (info->target_inbound_names[i], NULL);
      info->target_outbound_names[i] = name;
      assign = gimple_build_assign (name, info->default_values[i]);
      gsi_insert_before (gsi, assign, GSI_SAME_STMT);
      update_stmt (assign);
    }
  return assign;
}
