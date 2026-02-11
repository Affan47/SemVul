a2_get_source_filename_pair(void *ctx, const char *file)
{
    struct annotate_two *a2 = (struct annotate_two *) ctx;
    int ret;

    ret = commands_issue_command(a2->c, a2->client_command_list, ANNOTATE_LIST,
            file, 0);
    if (ret == -1) {
        logger_write_pos(logger, __FILE__, __LINE__,
                "commands_issue_command error");
        return -1;
    }

    ret = commands_issue_command(a2->c, a2->client_command_list,
            ANNOTATE_INFO_SOURCE_FILENAME_PAIR, file, 0);
    if (ret == -1) {
        logger_write_pos(logger, __FILE__, __LINE__,
                "commands_issue_command error");
        return -1;
    }

    return 0;
}
