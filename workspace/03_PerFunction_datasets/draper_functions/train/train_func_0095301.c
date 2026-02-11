fill_shd_status_for_local_bricks (dict_t *dict, glusterd_volinfo_t *volinfo)
{
        glusterd_brickinfo_t    *brickinfo = NULL;
        char                    msg[1024] = {0,};
        char                    key[1024]  = {0,};
        char                    value[1024] = {0,};
        int                     index = 0;
        int                     ret = 0;
        xlator_t               *this = NULL;

        this = THIS;
        snprintf (msg, sizeof (msg), "self-heal-daemon is not running on");

        list_for_each_entry (brickinfo, &volinfo->bricks, brick_list) {
                if (uuid_is_null (brickinfo->uuid))
                        (void)glusterd_resolve_brick (brickinfo);

                if (uuid_compare (MY_UUID, brickinfo->uuid)) {
                        index++;
                        continue;
                }
                snprintf (key, sizeof (key), "%d-status",index);
                snprintf (value, sizeof (value), "%s %s",msg,
                          uuid_utoa(MY_UUID));
                ret = dict_set_dynstr (dict, key, gf_strdup(value));
                if (ret) {
                        gf_log (this->name, GF_LOG_ERROR, "Unable to"
                                "set the dictionary for shd status msg");
                        goto out;
                }
                snprintf (key, sizeof (key), "%d-shd-status",index);
                ret = dict_set_str (dict, key, "off");
                if (ret) {
                        gf_log (this->name, GF_LOG_ERROR, "Unable to"
                                " set dictionary for shd status msg");
                        goto out;
                }

                index++;
        }

out:
        return ret;

}
