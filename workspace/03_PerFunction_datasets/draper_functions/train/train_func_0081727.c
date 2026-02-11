dsgw_valid_docname(char *filename)
{
    int dots = 0;
    char *local_filename = NULL;

    local_filename = filename;

    if (local_filename == NULL) {
	return(1);
    }

    for ( ; *local_filename; LDAP_UTF8INC(local_filename)) {


	if (!ldap_utf8isalnum(local_filename)) {


            if (*local_filename == '.') {
                if (local_filename == filename) {
                    return (0);
                }
                if (dots == 0) {

                    dots ++;
                    continue;
                }
            }


	    if (*local_filename == '-' || *local_filename == '_') {
		continue;
	    }

	    return (0);
	}
    }

    return(1);
}
