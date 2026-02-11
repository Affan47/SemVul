agentx_config_init(void)
{
    int agent_role = netsnmp_ds_get_boolean(NETSNMP_DS_APPLICATION_ID,
                                            NETSNMP_DS_AGENT_ROLE);


    netsnmp_register_default_domain("agentx", "unix tcp");
    netsnmp_register_default_target("agentx", "unix", NETSNMP_AGENTX_SOCKET);
#define val(x) __STRING(x)
    netsnmp_register_default_target("agentx", "tcp",
                                    "localhost:" val(AGENTX_PORT));
#undef val
    agentx_register_config_handler("agentxsocket",
                                  agentx_parse_agentx_socket, NULL,
                                  "AgentX bind address");
#ifdef USING_AGENTX_MASTER_MODULE


    if (MASTER_AGENT == agent_role) {
        snmpd_register_config_handler("master",
                                      agentx_parse_master, NULL,
                                      "specify 'agentx' for AgentX support");
    agentx_register_config_handler("agentxperms",
                                  agentx_parse_agentx_perms, NULL,
                                  "AgentX socket permissions: socket_perms [directory_perms [username|userid [groupname|groupid]]]");
    agentx_register_config_handler("agentxRetries",
                                  agentx_parse_agentx_retries, NULL,
                                  "AgentX Retries");
    agentx_register_config_handler("agentxTimeout",
                                  agentx_parse_agentx_timeout, NULL,
                                  "AgentX Timeout (seconds)");
    }
#endif

#ifdef USING_AGENTX_SUBAGENT_MODULE


    if (SUB_AGENT == agent_role) {


        netsnmp_ds_register_config(ASN_INTEGER,
                                   netsnmp_ds_get_string(NETSNMP_DS_LIBRARY_ID,
                                                         NETSNMP_DS_LIB_APPTYPE),
                                   "agentxPingInterval",
                                   NETSNMP_DS_APPLICATION_ID,
                                   NETSNMP_DS_AGENT_AGENTX_PING_INTERVAL);

        netsnmp_ds_set_int(NETSNMP_DS_APPLICATION_ID,
                           NETSNMP_DS_AGENT_AGENTX_PING_INTERVAL, 15);

    }
#endif
}
