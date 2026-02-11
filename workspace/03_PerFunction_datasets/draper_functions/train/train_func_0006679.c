glusterd_friend_contains_vol_bricks (glusterd_volinfo_t *volinfo,
                                     uuid_t friend_uuid)
{
        gf_boolean_t            ret = _gf_true;
        glusterd_brickinfo_t    *brickinfo = NULL;

        GF_ASSERT (volinfo);

        list_for_each_entry (brickinfo, &volinfo->bricks, brick_list) {
                if (uuid_compare (friend_uuid, brickinfo->uuid)) {
                        ret = _gf_false;
                        break;
                }
        }
        gf_log (THIS->name, GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
