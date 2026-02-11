AuthPLAIN(pal_socket_t socket, net_tools_t *nt, tConf *conf, tBrokerList **broker_list)
{
  char BufferIn[1024];
  char BufferOut[REDIRECT_RECEIVE_BUFFER_SIZE];
  char string[] = "AUTHENTICATE PLAIN\r\n";
  int Length;
  sint32_t tsp_status;


  if( nt->netsend(socket, string, sizeof(string)) == -1 )
  {
    Display(LOG_LEVEL_1, ELError, "AuthPLAIN", STR_NET_FAIL_W_SOCKET);
    return make_status(CTX_TSPAUTHENTICATION, ERR_SOCKET_IO);
  }

  memset(BufferIn, 0, sizeof(BufferIn));
  Length = pal_snprintf(BufferIn, sizeof(BufferIn), "%c%s%c%s\r\n", '\0', conf->userid, '\0', conf->passwd);


  if( nt->netsendrecv(socket, BufferIn, Length, BufferOut, sizeof(BufferOut)) == -1 )
  {
    Display(LOG_LEVEL_1, ELError, "AuthPLAIN", STR_NET_FAIL_RW_SOCKET);
    return make_status(CTX_TSPAUTHENTICATION, ERR_SOCKET_IO);
  }
  tsp_status = tspGetStatusCode(BufferOut);


  if( tspIsRedirectStatus(tsp_status) )
  {
    if( tspHandleRedirect(BufferOut, conf, broker_list) == TSP_REDIRECT_OK )
    {

      return make_status(CTX_TSPAUTHENTICATION, EVNT_BROKER_REDIRECTION);
    }
    else
    {

      return make_status(CTX_TSPAUTHENTICATION, ERR_BROKER_REDIRECTION);
    }
  }


  switch( tsp_status )
  {
  case TSP_PROTOCOL_SUCCESS:
    break;

  case TSP_PROTOCOL_AUTH_FAILED:
    Display(LOG_LEVEL_1, ELError, "AuthPLAIN", STR_TSP_AUTH_FAILED_USER, conf->userid);
    return make_status(CTX_TSPAUTHENTICATION, ERR_AUTHENTICATION_FAILURE);

  default:
    Display(LOG_LEVEL_1, ELError, "AuthPLAIN", STR_TSP_UNKNOWN_ERR_AUTH_FAILED, tspGetTspStatusStr(tsp_status));
    return make_status(CTX_TSPAUTHENTICATION, ERR_TSP_GENERIC_ERROR);
  }


  return make_status(CTX_TSPAUTHENTICATION, SUCCESS);
}
