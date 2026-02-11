load_env_data(const char *project, const char *flag, char **data)
{
    char *envname;
    char *envvalue;

    if (NULL == project || NULL == flag) return;

    asprintf(&envname, "%s_MPI%s", project, flag);
    if (NULL == (envvalue = getenv(envname))) {
        free(envname);
        asprintf(&envname, "%s_%s", project, flag);
        if (NULL == (envvalue = getenv(envname))) {
            free(envname);
            return;
        }
    }
    free(envname);

    if (NULL != *data) free(*data);
    *data = strdup(envvalue);
}
