sigar_log(sigar_t *sigar, int level, char *message)
{
    if (level > sigar->log_level) {
        return;
    }

    if (!sigar->log_impl) {
        return;
    }

    sigar->log_impl(sigar, sigar->log_data, level, message);
}
