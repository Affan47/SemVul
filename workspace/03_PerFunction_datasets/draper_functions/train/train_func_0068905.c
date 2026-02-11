_select_rxlators_for_full_self_heal (xlator_t *this,
                                     glusterd_volinfo_t *volinfo,
                                     dict_t *dict)
{
        glusterd_brickinfo_t    *brickinfo = NULL;
        glusterd_conf_t         *priv   = NULL;
        int                     index = 1;
        int                     rxlator_count = 0;
        int                     replica_count = 0;
        uuid_t                  candidate = {0};

        priv = this->private;
        replica_count = volinfo->replica_count;

        list_for_each_entry (brickinfo, &volinfo->bricks, brick_list) {
                if (uuid_is_null (brickinfo->uuid))
                        (void)glusterd_resolve_brick (brickinfo);

                if (uuid_compare (brickinfo->uuid, candidate) > 0)
                        uuid_copy (candidate, brickinfo->uuid);

                if (index % replica_count == 0) {
                        if (!uuid_compare (priv->uuid, candidate)) {
                                _add_rxlator_to_dict (dict, volinfo->volname,
                                                      (index-1)/replica_count,
                                                      rxlator_count);
                                rxlator_count++;
                        }
                        uuid_clear (candidate);
                }

                index++;
        }
        return rxlator_count;
}
