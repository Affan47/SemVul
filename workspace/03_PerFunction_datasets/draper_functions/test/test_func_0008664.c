commands_create_command(struct commands *c,
        enum annotate_commands com, const char *data)
{
    char *ncom = NULL;

    switch (com) {
        case ANNOTATE_INFO_SOURCES:
            ncom = strdup("server info sources\n");
            break;
        case ANNOTATE_LIST:
        {
            struct ibuf *temp_file_name = NULL;

            if (data != NULL) {
                temp_file_name = ibuf_init();
                ibuf_add(temp_file_name, data);
            }
            if (data == NULL)
                ncom = (char *) cgdb_malloc(sizeof (char) * (16));
            else
                ncom = (char *) cgdb_malloc(sizeof (char) * (18 +
                                strlen(data)));
            strcpy(ncom, "server list ");

            if (temp_file_name != NULL) {
                strcat(ncom, "\"");
                strcat(ncom, ibuf_get(temp_file_name));
                strcat(ncom, "\"");
                strcat(ncom, ":1");
            }


            if (temp_file_name == NULL) {
                ibuf_free(c->last_info_source_requested);
                c->last_info_source_requested = NULL;
            } else {
                if (c->last_info_source_requested == NULL)
                    c->last_info_source_requested = ibuf_init();

                ibuf_clear(c->last_info_source_requested);
                ibuf_add(c->last_info_source_requested,
                        ibuf_get(temp_file_name));
            }

            strcat(ncom, "\n");

            ibuf_free(temp_file_name);
            temp_file_name = NULL;
            break;
        }
        case ANNOTATE_INFO_LINE:
            ncom = strdup("server info line\n");
            break;
        case ANNOTATE_INFO_SOURCE_RELATIVE:
        case ANNOTATE_INFO_SOURCE_FILENAME_PAIR:
            ncom = strdup("server info source\n");
            break;
        case ANNOTATE_INFO_BREAKPOINTS:
            ncom = strdup("server info breakpoints\n");
            break;
        case ANNOTATE_TTY:
        {
            struct ibuf *temp_tty_name = ibuf_init();

            ibuf_add(temp_tty_name, data);
            ncom = (char *) cgdb_malloc(sizeof (char) * (13 + strlen(data)));
            strcpy(ncom, "server tty ");
            strcat(ncom, ibuf_get(temp_tty_name));
            strcat(ncom, "\n");

            ibuf_free(temp_tty_name);
            temp_tty_name = NULL;
            break;
        }
        case ANNOTATE_COMPLETE:
            ncom = (char *) cgdb_malloc(sizeof (char) * (18 + strlen(data)));
            strcpy(ncom, "server complete ");
            strcat(ncom, data);
            strcat(ncom, "\n");
            break;
        case ANNOTATE_SET_PROMPT:
            ncom = strdup(data);
            break;
        case ANNOTATE_VOID:
        default:
            logger_write_pos(logger, __FILE__, __LINE__, "switch error");
            break;
    };

    return ncom;
}
