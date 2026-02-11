snmp_config_when(char *line, int when)
{
    char           *cptr, buf[STRINGMAX];
    struct config_line *lptr = NULL;
    struct config_files *ctmp = config_files;
    char           *st;

    if (line == NULL) {
        config_perror("snmp_config() called with a null string.");
        return SNMPERR_GENERR;
    }

    strlcpy(buf, line, STRINGMAX);
    cptr = strtok_r(buf, SNMP_CONFIG_DELIMETERS, &st);
    if (!cptr) {
        netsnmp_config_warn("Wrong format: %s", line);
        return SNMPERR_GENERR;
    }
    if (cptr[0] == '[') {
        if (cptr[strlen(cptr) - 1] != ']') {
	    netsnmp_config_error("no matching ']' for type %s.", cptr + 1);
            return SNMPERR_GENERR;
        }
        cptr[strlen(cptr) - 1] = '\0';
        lptr = read_config_get_handlers(cptr + 1);
        if (lptr == NULL) {
	    netsnmp_config_error("No handlers regestered for type %s.",
				 cptr + 1);
            return SNMPERR_GENERR;
        }
        cptr = strtok_r(NULL, SNMP_CONFIG_DELIMETERS, &st);
        lptr = read_config_find_handler(lptr, cptr);
    } else {


        for (; ctmp != NULL && lptr == NULL; ctmp = ctmp->next)
            lptr = read_config_find_handler(ctmp->start, cptr);
    }
    if (lptr == NULL && netsnmp_ds_get_boolean(NETSNMP_DS_LIBRARY_ID,
					  NETSNMP_DS_LIB_NO_TOKEN_WARNINGS)) {
	netsnmp_config_warn("Unknown token: %s.", cptr);
        return SNMPERR_GENERR;
    }


    line = skip_white(line + (cptr - buf) + strlen(cptr) + 1);

    return (run_config_handler(lptr, cptr, line, when));
}
