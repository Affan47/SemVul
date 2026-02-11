glusterd_op_volume_dict_uuid_to_hostname (dict_t *dict, const char *key_fmt,
                                          int idx_min, int idx_max)
{
        int             ret = -1;
        int             i = 0;
        char            key[1024];
        char            *uuid_str = NULL;
        uuid_t          uuid = {0,};
        char            *hostname = NULL;
        xlator_t        *this = NULL;

        this = THIS;
        GF_ASSERT (this);

        GF_ASSERT (dict);
        GF_ASSERT (key_fmt);

        for (i = idx_min; i < idx_max; i++) {
                memset (key, 0, sizeof (key));
                snprintf (key, sizeof (key), key_fmt, i);
                ret = dict_get_str (dict, key, &uuid_str);
                if (ret)
                        continue;

                gf_log (this->name, GF_LOG_DEBUG, "Got uuid %s",
                        uuid_str);

                ret = uuid_parse (uuid_str, uuid);


                if (ret)
                        continue;

                hostname = glusterd_uuid_to_hostname (uuid);
                if (hostname) {
                        gf_log (this->name, GF_LOG_DEBUG, "%s -> %s",
                                uuid_str, hostname);
                        ret = dict_set_dynstr (dict, key, hostname);
                        if (ret) {
                                gf_log (this->name, GF_LOG_ERROR,
                                        "Error setting hostname %s to dict",
                                        hostname);
                                GF_FREE (hostname);
                                goto out;
                        }
                }
        }

out:
        gf_log (this->name, GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
