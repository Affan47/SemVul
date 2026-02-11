fetch_table(char *base, callback_t callback, void *pnt, int nof)
{
  int res = 0;

  struct snmp_session  session, *ss;
  struct snmp_pdu *pdu, *response;
  struct variable_list *vars;

  oid root[MAX_OID_LEN];
  oid    name[MAX_OID_LEN];
  size_t rootlen = MAX_OID_LEN;
  size_t namelen;

  int running;
  int status;

  snmp_sess_init( &session );

  init_snmp("disk_plugin");

  if(session.version == SNMP_DEFAULT_VERSION)
    session.version = netsnmp_ds_get_int(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_SNMPVERSION);

  session.peername = hostname;
  session.community = (unsigned char *)community;
  session.community_len = strlen(community);

  if(timeout)
    session.timeout = timeout  * 1000000L;

  if(!snmp_parse_oid(base, root, &rootlen))
  {
    return -1;
  }

  SOCK_STARTUP;

  ss = snmp_open(&session);

  if(!ss)
  {
    SOCK_CLEANUP;
    return -1;
  }

  memmove(name, root, rootlen * sizeof(oid));
  namelen = rootlen;

  running = -1;

  while(running)
  {
    pdu = snmp_pdu_create(SNMP_MSG_GETNEXT);
    snmp_add_null_var(pdu, name, namelen);

    status = snmp_synch_response(ss, pdu, &response);
    if(status != STAT_SUCCESS)
    {
      if(verbose)
        printf("%s: Error #1\n", bn);
      running = 0;
      res = -1;
      continue;
    }

    if(response->errstat != SNMP_ERR_NOERROR)
    {
      running = 0;
      if (response->errstat != SNMP_ERR_NOSUCHNAME)
      {
        if(verbose)
          printf("%s: Error #2\n", bn);
        res = -1;
      }
      continue;
    }

    for(vars = response->variables; vars; vars = vars->next_variable)
    {
      if((vars->name_length < rootlen) ||
         (memcmp(root, vars->name, rootlen * sizeof(oid)) != 0))
      {
        running = 0;
        continue;
      }

      if(verbose)
        printf("%s: Found another element\n", bn);


      callback(vars, &pnt);

      res++;


      if(nof && !(--nof))
      {
        running = 0;
        continue;
      }

      if ((vars->type != SNMP_ENDOFMIBVIEW) &&
          (vars->type != SNMP_NOSUCHOBJECT) &&
          (vars->type != SNMP_NOSUCHINSTANCE))
      {
        memmove((char *)name, (char *)vars->name,
                vars->name_length * sizeof(oid));

        namelen = vars->name_length;
      }
      else
      {
        running = 0;
      }
    }

    if(response)
      snmp_free_pdu(response);
  }

  snmp_close(ss);
  SOCK_CLEANUP;
  return res;
}
