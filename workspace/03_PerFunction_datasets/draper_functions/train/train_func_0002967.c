set_cmd_for_dev (int devno, struct BJNP_command *cmd, char cmd_code, int payload_len)
{


  strncpy (cmd->BJNP_id, device[devno].protocol_string, sizeof (cmd->BJNP_id));
  cmd->dev_type = BJNP_CMD_SCAN;
  cmd->cmd_code = cmd_code;
  cmd->unknown1 = htons (0);
  cmd->seq_no = htons (++(device[devno].serial));
  cmd->session_id = (cmd_code == CMD_UDP_POLL ) ? 0 : htons (device[devno].session_id);
  device[devno].last_cmd = cmd_code;
  cmd->payload_len = htonl (payload_len);
}
