free_param(param_t *param)
{
    if (param->allowedchars) {
        regfree(param->allowedchars);
        free(param->allowedchars);
    }

    if (param->allowedregexp) {
        regfree(param->allowedregexp);
        free(param->allowedregexp);
    }

    free(param);
}
