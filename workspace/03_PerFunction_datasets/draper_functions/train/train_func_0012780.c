glusterd_defrag_status_get (glusterd_volinfo_t *volinfo,
                            dict_t *dict)
{
        int      ret    = 0;
        uint64_t files  = 0;
        uint64_t size   = 0;
        uint64_t lookup = 0;

        if (!volinfo || !dict)
                goto out;

        ret = 0;
        if (volinfo->defrag_status == GF_DEFRAG_STATUS_NOT_STARTED)
                goto out;

        if (volinfo->defrag) {
                LOCK (&volinfo->defrag->lock);
                {
                        files  = volinfo->defrag->total_files;
                        size   = volinfo->defrag->total_data;
                        lookup = volinfo->defrag->num_files_lookedup;
                }
                UNLOCK (&volinfo->defrag->lock);
        } else {
                files  = volinfo->rebalance_files;
                size   = volinfo->rebalance_data;
                lookup = volinfo->lookedup_files;
        }

        ret = dict_set_uint64 (dict, "files", files);
        if (ret)
                gf_log (THIS->name, GF_LOG_WARNING,
                        "failed to set file count");

        ret = dict_set_uint64 (dict, "size", size);
        if (ret)
                gf_log (THIS->name, GF_LOG_WARNING,
                        "failed to set size of xfer");

        ret = dict_set_uint64 (dict, "lookups", lookup);
        if (ret)
                gf_log (THIS->name, GF_LOG_WARNING,
                        "failed to set lookedup file count");

        ret = dict_set_int32 (dict, "status", volinfo->defrag_status);
        if (ret)
                gf_log (THIS->name, GF_LOG_WARNING,
                        "failed to set status");

out:
        return 0;
}
