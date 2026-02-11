rpcsvc_set_allow_insecure (rpcsvc_t *svc, dict_t *options)
{
        int             ret = -1;
        char            *allow_insecure_str = NULL;
        gf_boolean_t    is_allow_insecure = _gf_false;

        GF_ASSERT (svc);
        GF_ASSERT (options);

        ret = dict_get_str (options, "rpc-auth-allow-insecure",
                            &allow_insecure_str);
        if (0 == ret) {
                ret = gf_string2boolean (allow_insecure_str,
                                         &is_allow_insecure);
                if (0 == ret) {
                        if (_gf_true == is_allow_insecure)
                                svc->allow_insecure = 1;
                        else
                                svc->allow_insecure = 0;
                }
        }

        return 0;
}
