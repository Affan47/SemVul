gf_defrag_status_get (gf_defrag_info_t *defrag, dict_t *dict)
{
        int      ret    = 0;
        uint64_t files  = 0;
        uint64_t size   = 0;
        uint64_t lookup = 0;
        uint64_t failures = 0;
        uint64_t skipped = 0;
        char     *status = "";
        double   elapsed = 0;
        struct timeval end = {0,};


        if (!defrag)
                goto out;

        ret = 0;
        if (defrag->defrag_status == GF_DEFRAG_STATUS_NOT_STARTED)
                goto out;

        files  = defrag->total_files;
        size   = defrag->total_data;
        lookup = defrag->num_files_lookedup;
        failures = defrag->total_failures;
        skipped = defrag->skipped;

        gettimeofday (&end, NULL);

        elapsed = end.tv_sec - defrag->start_time.tv_sec;

        if (!dict)
                goto log;

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


        ret = dict_set_int32 (dict, "status", defrag->defrag_status);
        if (ret)
                gf_log (THIS->name, GF_LOG_WARNING,
                        "failed to set status");
        if (elapsed) {
                ret = dict_set_double (dict, "run-time", elapsed);
                if (ret)
                        gf_log (THIS->name, GF_LOG_WARNING,
                                "failed to set run-time");
        }

        ret = dict_set_uint64 (dict, "failures", failures);
        if (ret)
                gf_log (THIS->name, GF_LOG_WARNING,
                        "failed to set failure count");

        ret = dict_set_uint64 (dict, "skipped", skipped);
        if (ret)
                gf_log (THIS->name, GF_LOG_WARNING,
                        "failed to set skipped file count");
log:
        switch (defrag->defrag_status) {
        case GF_DEFRAG_STATUS_NOT_STARTED:
                status = "not started";
                break;
        case GF_DEFRAG_STATUS_STARTED:
                status = "in progress";
                break;
        case GF_DEFRAG_STATUS_STOPPED:
                status = "stopped";
                break;
        case GF_DEFRAG_STATUS_COMPLETE:
                status = "completed";
                break;
        case GF_DEFRAG_STATUS_FAILED:
                status = "failed";
                break;
        }

        gf_log (THIS->name, GF_LOG_INFO, "Rebalance is %s. Time taken is %.2f "
                "secs", status, elapsed);
        gf_log (THIS->name, GF_LOG_INFO, "Files migrated: %"PRIu64", size: %"
                PRIu64", lookups: %"PRIu64", failures: %"PRIu64", skipped: "
                "%"PRIu64, files, size, lookup, failures, skipped);


out:
        return 0;
}
