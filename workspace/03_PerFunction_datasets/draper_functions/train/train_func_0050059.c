Clicmd_CAPABILITY(CLIENT_PARMS) {


    int cmdref;

    if (parsedcmdline->size() != 1) {
        snprintf(errstr, 1024, "Illegal capability request");
        return -1;
    }

    if ((cmdref =
         globalreg->kisnetserver->FetchProtocolRef(((*parsedcmdline)[0]).word)) < 0) {
        snprintf(errstr, 1024, "Unknown protocol: '%s'",
				 ((*parsedcmdline)[0]).word.c_str());
        return -1;
    }

    KisNetFramework::server_protocol *prot;

    if ((prot = globalreg->kisnetserver->FetchProtocol(cmdref)) == NULL) {
        snprintf(errstr, 1024, "Unable to fetch protocol info");
        return -1;
    }

    globalreg->kisnetserver->SendToClient(in_clid,
									  globalreg->netproto_map[PROTO_REF_CAPABILITY],
										  (void *) prot, NULL);

    return 1;
}
