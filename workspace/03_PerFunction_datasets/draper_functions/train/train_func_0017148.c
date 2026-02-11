logger_set_file(struct logger *log, const char *file)
{

    if (!log)
        return -1;

    if (!file)
        return -1;


    if (logger_close_writer(log) == -1)
        return -1;

    log->fd = fopen(file, "w");


    if (!log->fd) {
        printf("Error: Could not open file %s for writing\n", file);
        return -1;
    }

    log->log_file = strdup(file);

    return 0;
}
