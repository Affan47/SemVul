init (dict_t *this, char *key, data_t *value, void *data)
{
        void          *handle       = NULL;
        char          *auth_file    = NULL;
        auth_handle_t *auth_handle  = NULL;
        auth_fn_t      authenticate = NULL;
        int           *error        = NULL;
        int            ret          = 0;


        error = data;

        if (!strncasecmp (key, "ip", strlen ("ip"))) {
                gf_log ("authenticate", GF_LOG_ERROR,
                        "AUTHENTICATION MODULE \"IP\" HAS BEEN REPLACED "
                        "BY \"ADDR\"");
                dict_set (this, key, data_from_dynptr (NULL, 0));


                key = "addr";
        }

        ret = gf_asprintf (&auth_file, "%s/%s.so", LIBDIR, key);
        if (-1 == ret) {
                dict_set (this, key, data_from_dynptr (NULL, 0));
                *error = -1;
                return -1;
        }

        handle = dlopen (auth_file, RTLD_LAZY);
        if (!handle) {
                gf_log ("authenticate", GF_LOG_ERROR, "dlopen(%s): %s\n",
                        auth_file, dlerror ());
                dict_set (this, key, data_from_dynptr (NULL, 0));
                GF_FREE (auth_file);
                *error = -1;
                return -1;
        }
        GF_FREE (auth_file);

        authenticate = dlsym (handle, "gf_auth");
        if (!authenticate) {
                gf_log ("authenticate", GF_LOG_ERROR,
                        "dlsym(gf_auth) on %s\n", dlerror ());
                dict_set (this, key, data_from_dynptr (NULL, 0));
                dlclose (handle);
                *error = -1;
                return -1;
        }

        auth_handle = GF_CALLOC (1, sizeof (*auth_handle),
                                 gf_common_mt_auth_handle_t);
        if (!auth_handle) {
                dict_set (this, key, data_from_dynptr (NULL, 0));
                *error = -1;
                dlclose (handle);
                return -1;
        }
        auth_handle->vol_opt = GF_CALLOC (1, sizeof (volume_opt_list_t),
                                          gf_common_mt_volume_opt_list_t);
        if (!auth_handle->vol_opt) {
                dict_set (this, key, data_from_dynptr (NULL, 0));
                *error = -1;
                GF_FREE (auth_handle);
                dlclose (handle);
                return -1;
        }
        auth_handle->vol_opt->given_opt = dlsym (handle, "options");
        if (auth_handle->vol_opt->given_opt == NULL) {
                gf_log ("authenticate", GF_LOG_DEBUG,
                        "volume option validation not specified");
        }

        auth_handle->authenticate = authenticate;
        auth_handle->handle = handle;

        dict_set (this, key,
                  data_from_dynptr (auth_handle, sizeof (*auth_handle)));
        return 0;
}
