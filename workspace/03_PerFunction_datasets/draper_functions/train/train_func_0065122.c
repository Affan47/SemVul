authBasicParse(authScheme * scheme, int n_configured, char *param_str)
{
    if (scheme->scheme_data == NULL) {
	assert(basicConfig == NULL);

	scheme->scheme_data = xmalloc(sizeof(auth_basic_config));
	memset(scheme->scheme_data, 0, sizeof(auth_basic_config));
	basicConfig = scheme->scheme_data;
	basicConfig->basicAuthRealm = xstrdup("Squid proxy-caching web server");
	basicConfig->authenticateChildren = 5;
	basicConfig->credentialsTTL = 2 * 60 * 60;
    }
    basicConfig = scheme->scheme_data;
    if (strcasecmp(param_str, "program") == 0) {
	if (basicConfig->authenticate)
	    wordlistDestroy(&basicConfig->authenticate);
	parse_wordlist(&basicConfig->authenticate);
    } else if (strcasecmp(param_str, "children") == 0) {
	parse_int(&basicConfig->authenticateChildren);
    } else if (strcasecmp(param_str, "concurrency") == 0) {
	parse_int(&basicConfig->authenticateConcurrency);
    } else if (strcasecmp(param_str, "realm") == 0) {
	parse_eol(&basicConfig->basicAuthRealm);
    } else if (strcasecmp(param_str, "credentialsttl") == 0) {
	parse_time_t(&basicConfig->credentialsTTL);
    } else if (strcasecmp(param_str, "casesensitive") == 0) {
	parse_onoff(&basicConfig->casesensitive);
    } else if (strcasecmp(param_str, "blankpassword") == 0) {
	parse_onoff(&basicConfig->blankpassword);
    } else if (strcasecmp(param_str, "utf8") == 0) {
	parse_onoff(&basicConfig->utf8);
    } else {
	debug(29, 0) ("unrecognised basic auth scheme parameter '%s'\n", param_str);
    }
}
