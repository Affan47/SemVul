internal_register_config_handler(const char *type_param,
				 const char *token,
				 void (*parser) (const char *, char *),
				 void (*releaser) (void), const char *help,
				 int when)
{
    struct config_files **ctmp = &config_files;
    struct config_line  **ltmp;
    const char           *type = type_param;

    if (type == NULL || *type == '\0') {
        type = netsnmp_ds_get_string(NETSNMP_DS_LIBRARY_ID,
				     NETSNMP_DS_LIB_APPTYPE);
    }


    if (strchr(type, ':')) {
        struct config_line *ltmp2 = NULL;
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
            ltmp2 = internal_register_config_handler(c, token, parser,
                                                     releaser, help, when);
        }
        return ltmp2;
    }


    while (*ctmp != NULL && strcmp((*ctmp)->fileHeader, type)) {
        ctmp = &((*ctmp)->next);
    }

    if (*ctmp == NULL) {
        *ctmp = (struct config_files *)
            calloc(1, sizeof(struct config_files));
        if (!*ctmp) {
            return NULL;
        }

        (*ctmp)->fileHeader = strdup(type);
        DEBUGMSGTL(("9:read_config:type", "new type %s\n", type));
    }

    DEBUGMSGTL(("9:read_config:register_handler", "registering %s %s\n",
                type, token));


    ltmp = &((*ctmp)->start);

    while (*ltmp != NULL && strcmp((*ltmp)->config_token, token)) {
        ltmp = &((*ltmp)->next);
    }

    if (*ltmp == NULL) {
        *ltmp = (struct config_line *)
            calloc(1, sizeof(struct config_line));
        if (!*ltmp) {
            return NULL;
        }

        (*ltmp)->config_time = when;
        (*ltmp)->config_token = strdup(token);
        if (help != NULL)
            (*ltmp)->help = strdup(help);
    }


    (*ltmp)->parse_line = parser;
    (*ltmp)->free_func = releaser;

    return (*ltmp);

}
