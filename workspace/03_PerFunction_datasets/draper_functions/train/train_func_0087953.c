consume_supp_cmds(int index) {

  struct msg_struct *msg = NULL;
  struct cmd_struct *cmd;
  socket_info_type* socket_info;
  Sim_entry_type *sim;

  socket_info = &(steerer_socket_info_table.socket_info[index]);
  sim = &(Sim_table.sim[index]);


  if(socket_info->comms_status != REG_COMMS_STATUS_CONNECTED) {
#ifdef REG_DEBUG
    fprintf(stderr, "consume_supp_cmds: Not connected!\n");
#endif
    return REG_FAILURE;
  }

  msg = Get_status_msg_impl(index, REG_FALSE);
  if(msg) {
    cmd = msg->supp_cmd->first_cmd;

    while(cmd) {
      sscanf((char *)(cmd->id), "%d",
	     &(sim->Cmds_table.cmd[sim->Cmds_table.num_registered].cmd_id));


#ifdef REG_DEBUG
      fprintf(stderr, "cmd->id %s: parsed %d\n", cmd->id, sim->Cmds_table.cmd[sim->Cmds_table.num_registered].cmd_id);
#endif

      Increment_cmd_registered(&(sim->Cmds_table));

      cmd = cmd->next;
    }

    Delete_msg_struct(&msg);
  }
  else {
    fprintf(stderr, "consume_supp_cmds: error parsing cmds\n");
    return REG_FAILURE;
  }

  return REG_SUCCESS;
}
