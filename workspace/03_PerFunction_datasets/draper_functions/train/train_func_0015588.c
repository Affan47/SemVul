cpl_parameter_set_alias(cpl_parameter *self, cpl_parameter_mode mode,
                        const char *alias)
{


    if (self == NULL) {
        return cpl_error_set(cpl_func, CPL_ERROR_NULL_INPUT);
    }

    switch (mode) {
    case CPL_PARAMETER_MODE_CLI:
        if (self->info.c_key) {
            cx_free(self->info.c_key);
        }
        self->info.c_key = cx_strdup(alias);
        break;

    case CPL_PARAMETER_MODE_ENV:
        if (self->info.e_key) {
            cx_free(self->info.e_key);
        }
        self->info.e_key = cx_strdup(alias);
        break;

    case CPL_PARAMETER_MODE_CFG:
        if (self->info.f_key) {
            cx_free(self->info.f_key);
        }
        self->info.f_key = cx_strdup(alias);
        break;

    default:
        return cpl_error_set_message(cpl_func, CPL_ERROR_ILLEGAL_INPUT,
                                     "%s, mode=%d, alias=%s",
                                     cpl_parameter_get_name(self), (int)mode,
                                     alias);
    }

    return CPL_ERROR_NONE;

}
