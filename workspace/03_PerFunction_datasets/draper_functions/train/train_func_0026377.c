free_config()
{
    if (config.cfilter.bf_insns != NULL) free (config.cfilter.bf_insns);

    if (config.pidfile != NULL) free(config.pidfile);
    if (config.user_name != NULL) free(config.user_name);
    if (config.group_name != NULL) free(config.group_name);
    if (config.bpff != NULL) free(config.bpff);
}
