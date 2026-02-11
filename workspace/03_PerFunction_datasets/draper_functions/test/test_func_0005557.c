ldap_exists(LDAP *ld, LDAPMessage *e, char *attr,
                                                  char *vstr, int cs)
{
	char **vals;
	int    count, at;

	if (ld == NULL || e == NULL || attr == NULL || vstr == NULL)
		misc_die(FL, "ldap_exists: ?ld? ?e? ?attr? ?vstr?");


	if ((vals = ldap_get_values(ld, e, attr)) == NULL) {
#if defined(COMPILE_DEBUG)
		debug(3, "LDAP result: no values for '%.256s'", attr);
#endif
		return -1;
	}

	count = ldap_count_values(vals);
	if(cs) {
		for(at=0; at < count; at++) {
#if defined(COMPILE_DEBUG)
		debug(3, "LDAP result: checking[%d:%d] '%.256s'='%.1024s'",
		                              count-1, at, attr, vals[at]);
#endif
			if(misc_strequ(vals[at], vstr)) {
				ldap_value_free(vals);
				return 0;
			}
		}
	} else {
		for(at=0; at < count; at++) {
#if defined(COMPILE_DEBUG)
		debug(3, "LDAP result: checking[%d:%d] '%.256s'='%.1024s'",
		                              count-1, at, attr, vals[at]);
#endif
			if(misc_strcaseequ(vals[at], vstr)) {
				ldap_value_free(vals);
				return 0;
			}
		}
	}
	ldap_value_free(vals);

#if defined(COMPILE_DEBUG)
		debug(3, "LDAP result: '%.256s'='%.1024s' not found",
		                       attr, vstr);
#endif

	return 1;
}
