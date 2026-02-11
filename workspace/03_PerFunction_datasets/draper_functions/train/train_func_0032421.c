apcmastersnmp_set_config(StonithPlugin * s, StonithNVpair * list)
{
	struct pluginDevice* sd = (struct pluginDevice *)s;
	int	rc;
	int *	i;
	StonithNamesToGet	namestocopy [] =
	{	{ST_IPADDR,	NULL}
	,	{ST_PORT,	NULL}
	,	{ST_COMMUNITY,	NULL}
	,	{NULL,		NULL}
	};

	DEBUGCALL;
	ERRIFWRONGDEV(s,S_INVAL);
	if (sd->sp.isconfigured) {
		return S_OOPS;
	}

	if ((rc=OurImports->CopyAllValues(namestocopy, list)) != S_OK) {
		return rc;
	}
	sd->hostname = namestocopy[0].s_value;
	sd->port = atoi(namestocopy[1].s_value);
	PluginImports->mfree(namestocopy[1].s_value);
	sd->community = namestocopy[2].s_value;


	if (gethostbyname(sd->hostname) != NULL) {

		init_snmp("apcmastersnmp");


		if ((sd->sptr = APC_open(sd->hostname, sd->port, sd->community)) != NULL) {


			if ((i = APC_read(sd->sptr, OID_NUM_OUTLETS, ASN_INTEGER))
                    		== NULL) {
				LOG(PIL_CRIT
				, "%s: cannot read number of outlets."
				,       __FUNCTION__);
				return (S_ACCESS);
			}

			sd->num_outlets = *i;
			if (Debug) {
				LOG(PIL_DEBUG, "%s: number of outlets: %i."
				,       __FUNCTION__, sd->num_outlets );
			}


			return (S_OK);
		}else{
			LOG(PIL_CRIT, "%s: cannot create snmp session."
			,       __FUNCTION__);
		}
	}else{
		LOG(PIL_CRIT, "%s: cannot resolve hostname '%s', h_errno %d."
		,       __FUNCTION__, sd->hostname, h_errno);
	}


	return (S_BADCONFIG);
}
