mca_base_param_find_string_name(const char *type,
                                    const char *param_name,
                                    char **env,
                                    char **current_value)
{
    char *tmp, *ptr;
    int len, i;
    int rc=OPAL_ERR_NOT_FOUND;

    if (NULL == env) {
        return OPAL_ERR_NOT_FOUND;
    }

    asprintf(&tmp, "%s%s_%s", mca_prefix, type, param_name);
    len = strlen(tmp);
    for (i=0; NULL != env[i]; i++) {
        if (0 == strncmp(tmp, env[i], len)) {
            ptr = strchr(env[i], '=');
            ptr++;
            *current_value = ptr;
            rc = OPAL_SUCCESS;
            break;
        }
    }
    free(tmp);
    return rc;
}
