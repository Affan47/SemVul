proc_module_get_self(void *data, char *name, int len)
{
    sigar_t *sigar = (sigar_t *)data;
    char *ptr = rindex(name, '/');

    if (!ptr) {
        return SIGAR_OK;
    }

    if (strnEQ(ptr+1, "libsigar-", 9)) {
        int offset = ptr - name;

        sigar->self_path = sigar_strdup(name);
        *(sigar->self_path + offset) = '\0';

        if (SIGAR_LOG_IS_DEBUG(sigar)) {
            sigar_log_printf(sigar, SIGAR_LOG_DEBUG,
                             "detected sigar-lib='%s'",
                             sigar->self_path);
        }

        return !SIGAR_OK;
    }

    return SIGAR_OK;
}
