convert_to_openldap_uri( const char *hostname_or_uri, int port,
                         const char *proto )
{
    char *retstr = NULL;
    char *my_copy = NULL;
    char *start = NULL;
    char *iter = NULL;
    char *s = NULL;
    const char *brkstr = " ";

    if (!hostname_or_uri) {
	return NULL;
    }

    my_copy = dsgw_ch_strdup(hostname_or_uri);

    if (!proto && !PL_strncasecmp(my_copy, "ldap", 4)) {
	start = my_copy + 4;
	if ((*start == 's') || (*start == 'i')) {
	    start++;
	}
	if (!PL_strncmp(start, "://", 3)) {
	    *start = '\0';
	    proto = my_copy;
	    start += 3;
	} else {
	    dsgw_error( DSGW_ERR_LDAPINIT, NULL, DSGW_ERROPT_EXIT, 0, NULL );
	}
    } else if (!proto) {
	dsgw_error( DSGW_ERR_LDAPINIT, NULL, DSGW_ERROPT_EXIT, 0, NULL );
    } else {
	start = my_copy;
    }

    for (s = ldap_utf8strtok_r(my_copy, brkstr, &iter); s != NULL;
	 s = ldap_utf8strtok_r(NULL, brkstr, &iter)) {
	char *ptr;
	int last = 0;


	if ((ptr = strchr(s, '/'))) {
	    *ptr = '\0';
	    last = 1;
	}
	if (retstr) {
	    retstr = PR_sprintf_append(retstr, "/ %s://%s", proto, s);
	} else {
	    retstr = PR_smprintf("%s://%s", proto, s);
	}
	if (last) {
	    break;
	}
    }


    retstr = PR_sprintf_append(retstr, ":%d/", port);
    free(my_copy);
    return retstr;
}
