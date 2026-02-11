fcgi_config_set_env_var(pool *p, char **envp, unsigned int *envc, char * var)
{
    if (*envc >= MAX_INIT_ENV_VARS) {
        return "too many variables, must be <= MAX_INIT_ENV_VARS";
    }

    if (strchr(var, '=') == NULL) {
        *(envp + *envc) = ap_pstrcat(p, var, "=", getenv(var), NULL);
    }
    else {
        *(envp + *envc) = var;
    }

    (*envc)++;

    return NULL;
}
