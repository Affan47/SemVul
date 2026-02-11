sasl_map_config_add(Slapi_PBlock *pb, Slapi_Entry* entryBefore, Slapi_Entry* e, int *returncode, char *returntext, void *arg)
{
	int ret = 0;
	sasl_map_data *dp = NULL;
	sasl_map_private *priv = sasl_map_get_global_priv();
	LDAPDebug( LDAP_DEBUG_TRACE, "-> sasl_map_config_add\n", 0, 0, 0 );
	ret = sasl_map_config_parse_entry(entryBefore,&dp);
	if (!ret && dp) {
		ret = sasl_map_insert_list_entry(priv,dp);
	}
	if (0 == ret) {
		ret = SLAPI_DSE_CALLBACK_OK;
	} else {
		returntext = "sasl map entry rejected";
		*returncode = LDAP_UNWILLING_TO_PERFORM;
		ret = SLAPI_DSE_CALLBACK_ERROR;
	}
	LDAPDebug( LDAP_DEBUG_TRACE, "<- sasl_map_config_add\n", 0, 0, 0 );
	return ret;
}
