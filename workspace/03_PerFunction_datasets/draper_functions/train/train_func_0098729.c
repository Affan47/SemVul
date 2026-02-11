bjnp_get_scanner_mac_address ( int devno, char *mac_address )
{


  char cmd_buf[BJNP_CMD_MAX];
  char resp_buf[BJNP_RESP_MAX];
  int resp_len;
  struct DISCOVER_RESPONSE *resp = (struct DISCOVER_RESPONSE * )&resp_buf;;


  set_cmd_for_dev (devno, (struct BJNP_command *) cmd_buf, CMD_UDP_DISCOVER, 0);
  resp_len = udp_command (devno, cmd_buf,
			  sizeof (struct BJNP_command), resp_buf,
			  BJNP_RESP_MAX);

  if (resp_len > 0)
    {
      PDBG (bjnp_dbg (LOG_DEBUG2, "bjnp_get_scanner_mac_address: Discover response:\n"));
      PDBG (bjnp_hexdump (LOG_DEBUG2, resp_buf, resp_len));
      u8tohex( mac_address, resp -> mac_addr, sizeof( resp -> mac_addr ) );
      return 0;
    }
  return -1;
}
