netsnmp_add_traphandler(Netsnmp_Trap_Handler* handler,
                        oid *trapOid, int trapOidLen ) {
    netsnmp_trapd_handler *traph, *traph2;

    if ( !handler )
        return NULL;

    traph = SNMP_MALLOC_TYPEDEF(netsnmp_trapd_handler);
    if ( !traph )
        return NULL;


    traph->authtypes   = TRAP_AUTH_ALL;
    traph->handler     = handler;
    traph->trapoid_len = trapOidLen;
    traph->trapoid     = snmp_duplicate_objid(trapOid, trapOidLen);


    for (traph2 = netsnmp_specific_traphandlers;
         traph2; traph2 = traph2->nextt) {

        if (snmp_oid_compare(traph2->trapoid, traph2->trapoid_len,
                             trapOid, trapOidLen) <= 0)
	    break;
    }
    if (traph2) {


        if (!snmp_oid_compare(traph->trapoid,  traph->trapoid_len,
                              traph2->trapoid, traph2->trapoid_len)) {


            while (traph2->nexth)
                traph2 = traph2->nexth;
            traph2->nexth = traph;
            traph->nextt  = traph2->nextt;
            traph->prevt  = traph2->prevt;
        } else {


            traph->prevt  = traph2->prevt;
            if (traph2->prevt)
	        traph2->prevt->nextt = traph;
            else
	        netsnmp_specific_traphandlers = traph;
            traph2->prevt = traph;
            traph->nextt  = traph2;
        }
    } else {


	if (netsnmp_specific_traphandlers) {
            traph2 = netsnmp_specific_traphandlers;
            while (traph2->nextt)
                traph2 = traph2->nextt;
            traph2->nextt = traph;
            traph->prevt  = traph2;
	} else {


            netsnmp_specific_traphandlers = traph;
        }
    }

    return traph;
}
