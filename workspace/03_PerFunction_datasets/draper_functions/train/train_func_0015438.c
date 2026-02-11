commands_parse_source(struct commands *c,
        struct tgdb_list *client_command_list,
        const char *buf, size_t n, struct tgdb_list *list)
{
    int i = 0;
    char copy[n + 1];
    char *cur = copy + n;
    struct ibuf *file = ibuf_init(), *line = ibuf_init();

    strncpy(copy, buf, n + 1);

    while (cur != copy && i <= 3) {
        if (*cur == ':') {
            if (i == 3) {
                int length = strlen(cur + 1);
                char *temp = cgdb_malloc(sizeof (char) * (length + 1));

                if (sscanf(cur + 1, "%s", temp) != 1)
                    logger_write_pos(logger, __FILE__, __LINE__,
                            "Could not get line number");

                ibuf_add(line, temp);
                free(temp);
                temp = NULL;
            }

            *cur = '\0';
            ++i;
        }
        --cur;
    }

    {
        int length = strlen(copy);
        char *temp = cgdb_malloc(sizeof (char) * (length + 1));

        if (strncmp("source ", copy, 7) == 0 && length > 7) {
            int j;

            for (j = 7; j < length; j++)
                ibuf_addchar(file, copy[j]);
        } else {
            logger_write_pos(logger, __FILE__, __LINE__,
                    "Could not get file name out of line (%s)", buf);
        }

        free(temp);
        temp = NULL;
    }

    ibuf_clear(c->absolute_path);
    ibuf_add(c->absolute_path, ibuf_get(file));
    ibuf_clear(c->line_number);
    ibuf_add(c->line_number, ibuf_get(line));

    ibuf_free(file);
    ibuf_free(line);


    if (commands_issue_command(c,
                    client_command_list,
                    ANNOTATE_INFO_SOURCE_RELATIVE, NULL, 1) == -1) {
        logger_write_pos(logger, __FILE__, __LINE__,
                "commands_issue_command error");
        return -1;
    }

    return 0;
}
