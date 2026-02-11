get_rdn_plus_uniqueid(char *sessionid, const char *olddn, const char *uniqueid)
{
	char *newrdn;

	Slapi_DN *sdn= slapi_sdn_new_dn_byval(olddn);
	Slapi_RDN *rdn= slapi_rdn_new();
	slapi_sdn_get_rdn(sdn,rdn);
	PR_ASSERT(uniqueid!=NULL);
	if(slapi_rdn_contains(rdn,SLAPI_ATTR_UNIQUEID,uniqueid,strlen(uniqueid)))
	{


		slapi_log_error(SLAPI_LOG_FATAL, sessionid,
				"Annotated DN %s has naming conflict\n", olddn );
		newrdn= NULL;
	}
	else
	{
		slapi_rdn_add(rdn,SLAPI_ATTR_UNIQUEID,uniqueid);
		newrdn= slapi_ch_strdup(slapi_rdn_get_rdn(rdn));
	}
	slapi_sdn_free(&sdn);
	slapi_rdn_free(&rdn);
	return newrdn;
}
