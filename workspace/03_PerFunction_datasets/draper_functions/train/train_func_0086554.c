log_destroy(void)
{
    loglvl = LOG_NONE;

    if (logf != stderr)
        fclose(logf);
}
