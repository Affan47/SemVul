set_cmd_envvars(fcgid_cmd_env *cmdenv, apr_table_t *envvars)
{
    const apr_array_header_t *envvars_arr;
    const apr_table_entry_t *envvars_entry;
    int i;
    int overflow = 0;

    if (envvars) {
        envvars_arr = apr_table_elts(envvars);
        envvars_entry = (apr_table_entry_t *) envvars_arr->elts;
        if (envvars_arr->nelts > INITENV_CNT) {
            overflow = envvars_arr->nelts - INITENV_CNT;
        }

        for (i = 0; i < envvars_arr->nelts && i < INITENV_CNT; ++i) {
            if (envvars_entry[i].key == NULL
                || envvars_entry[i].key[0] == '\0')
                break;
            apr_cpystrn(cmdenv->initenv_key[i], envvars_entry[i].key,
                        INITENV_KEY_LEN);
            apr_cpystrn(cmdenv->initenv_val[i], envvars_entry[i].val,
                        INITENV_VAL_LEN);
        }
        if (i < INITENV_CNT) {
            cmdenv->initenv_key[i][0] = '\0';
        }
    }
    else {
        cmdenv->initenv_key[0][0] = '\0';
    }

    return overflow;
}
