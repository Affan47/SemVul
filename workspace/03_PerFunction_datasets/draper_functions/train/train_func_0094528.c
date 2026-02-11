glusterd_validate_volume_id (dict_t *op_dict, glusterd_volinfo_t *volinfo)
{
        int     ret             = -1;
        char    *volid_str      = NULL;
        uuid_t  vol_uid         = {0, };
        xlator_t *this          = NULL;

        this = THIS;
        GF_ASSERT (this);

        ret = dict_get_str (op_dict, "vol-id", &volid_str);
        if (ret) {
                gf_log (this->name, GF_LOG_ERROR, "Failed to get volume id for "
                        "volume %s", volinfo->volname);
                goto out;
        }
        ret = uuid_parse (volid_str, vol_uid);
        if (ret) {
                gf_log (this->name, GF_LOG_ERROR, "Failed to parse volume id "
                        "for volume %s", volinfo->volname);
                goto out;
        }

        if (uuid_compare (vol_uid, volinfo->volume_id)) {
                gf_log (this->name, GF_LOG_ERROR, "Volume ids of volume %s - %s"
                        " and %s - are different. Possibly a split brain among "
                        "peers.", volinfo->volname, volid_str,
                        uuid_utoa (volinfo->volume_id));
                ret = -1;
                goto out;
        }

out:
        return ret;
}
