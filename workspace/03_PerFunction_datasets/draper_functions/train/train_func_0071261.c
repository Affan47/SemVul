glusterd_defrag_volume_status_update (glusterd_volinfo_t *volinfo,
                                      dict_t *rsp_dict)
{
        int                             ret = 0;
        uint64_t                        files = 0;
        uint64_t                        size = 0;
        uint64_t                        lookup = 0;
        gf_defrag_status_t              status = GF_DEFRAG_STATUS_NOT_STARTED;
        uint64_t                        failures = 0;
        xlator_t                       *this = NULL;

        this = THIS;

        ret = dict_get_uint64 (rsp_dict, "files", &files);
        if (ret)
                gf_log (this->name, GF_LOG_TRACE,
                        "failed to get file count");

        ret = dict_get_uint64 (rsp_dict, "size", &size);
        if (ret)
                gf_log (this->name, GF_LOG_TRACE,
                        "failed to get size of xfer");

        ret = dict_get_uint64 (rsp_dict, "lookups", &lookup);
        if (ret)
                gf_log (this->name, GF_LOG_TRACE,
                        "failed to get lookedup file count");

        ret = dict_get_int32 (rsp_dict, "status", (int32_t *)&status);
        if (ret)
                gf_log (this->name, GF_LOG_TRACE,
                        "failed to get status");

        ret = dict_get_uint64 (rsp_dict, "failures", &failures);
        if (ret)
                gf_log (this->name, GF_LOG_TRACE,
                        "failed to get failure count");

        if (files)
                volinfo->rebalance_files = files;
        if (size)
                volinfo->rebalance_data = size;
        if (lookup)
                volinfo->lookedup_files = lookup;
        if (status)
                volinfo->defrag_status = status;
        if (failures)
                volinfo->rebalance_failures = failures;

        return ret;
}
