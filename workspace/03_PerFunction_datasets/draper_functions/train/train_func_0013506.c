agmt_set_transportinfo_no_lock(Repl_Agmt *ra, const Slapi_Entry *e)
{
	char *tmpstr;
	int rc = 0;

	tmpstr = slapi_entry_attr_get_charptr(e, type_nsds5TransportInfo);
	if (!tmpstr || !strcasecmp(tmpstr, "LDAP")) {
		ra->transport_flags = 0;
	} else if (strcasecmp(tmpstr, "SSL") == 0) {
		ra->transport_flags = TRANSPORT_FLAG_SSL;
	} else if (strcasecmp(tmpstr, "TLS") == 0) {
		ra->transport_flags = TRANSPORT_FLAG_TLS;
	}


	slapi_ch_free_string(&tmpstr);
	return (rc);
}
