_sasl_getconfpath(void *context __attribute__((unused)),
                  char ** path_dest)
{
#if !defined(WIN32)
    char *path;
#endif
    int res = SASL_OK;

    if (! path_dest) {
        return SASL_BADPARAM;
    }


    if (default_conf_path == NULL) {

#if defined(WIN32)

        default_conf_path = _sasl_get_default_win_path(context,
                                                       SASL_CONF_PATH_ATTR,
                                                       CONFIGDIR);
#else

        path = _sasl_get_default_unix_path(context,
                                           SASL_CONF_PATH_ENV_VAR,
                                           CONFIGDIR);

        res = _sasl_strdup(path, &default_conf_path, NULL);
#endif
    }

    if (res == SASL_OK) {
        *path_dest = default_conf_path;
    }

    return res;
}
