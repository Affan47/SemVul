tspConnect( pal_socket_t *p_sock, char *srvname, uint16_t srvport, net_tools_t *nt )
{
  sint32_t ret;
  gogoc_status status = STATUS_SUCCESS_INIT;


  ret = nt->netopen( p_sock, srvname, srvport );
  switch( ret )
  {
  case 0:
    status = make_status(CTX_NETWORKCONNECT, SUCCESS); break;

  case -1:
    status = make_status(CTX_NETWORKCONNECT, ERR_FAIL_RESOLV_ADDR); break;

  case -2:
    status = make_status(CTX_NETWORKCONNECT, ERR_FAIL_SOCKET_CONNECT); break;
  }

  return status;
}
