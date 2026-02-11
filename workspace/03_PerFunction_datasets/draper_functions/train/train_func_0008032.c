unregister_config_handler(const char *type_param, const char *token)
{
    struct config_files **ctmp = &config_files;
    struct config_line  **ltmp;
    const char           *type = type_param;

    if (type == NULL || *type == '\0') {
        type = netsnmp_ds_get_string(NETSNMP_DS_LIBRARY_ID,
				     NETSNMP_DS_LIB_APPTYPE);
    }


    if (strchr(type, ':')) {
        char                buf[STRINGMAX];
        char               *cptr = buf;

        strlcpy(buf, type, STRINGMAX);
        while (cptr) {
            char* c = cptr;
            cptr = strchr(cptr, ':');
            if(cptr) {
                *cptr = '\0';
                ++cptr;
            }
            unregister_config_handler(c, token);
        }
        return;
    }


    while (*ctmp != NULL && strcmp((*ctmp)->fileHeader, type)) {
        ctmp = &((*ctmp)->next);
    }

    if (*ctmp == NULL) {


        return;
    }

    ltmp = &((*ctmp)->start);
    if (*ltmp == NULL) {


        return;
    }
    if (strcmp((*ltmp)->config_token, token) == 0) {


        struct config_line *ltmp2 = (*ltmp)->next;
        if ((*ltmp)->free_func)
            (*ltmp)->free_func();
        SNMP_FREE((*ltmp)->config_token);
        SNMP_FREE((*ltmp)->help);
        SNMP_FREE(*ltmp);
        (*ctmp)->start = ltmp2;
        return;
    }
    while ((*ltmp)->next != NULL
           && strcmp((*ltmp)->next->config_token, token)) {
        ltmp = &((*ltmp)->next);
    }
    if ((*ltmp)->next != NULL) {
        struct config_line *ltmp2 = (*ltmp)->next->next;
        if ((*ltmp)->next->free_func)
            (*ltmp)->next->free_func();
        SNMP_FREE((*ltmp)->next->config_token);
        SNMP_FREE((*ltmp)->next->help);
        SNMP_FREE((*ltmp)->next);
        (*ltmp)->next = ltmp2;
    }
}
