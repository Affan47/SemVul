io_stats_dump_global (xlator_t *this, struct ios_global_stats *stats,
                      struct timeval *now, int interval,
                      struct ios_dump_args *args)
{
        int     ret = -1;

        GF_ASSERT (args);
        GF_ASSERT (now);
        GF_ASSERT (stats);
        GF_ASSERT (this);


        switch (args->type) {
        case IOS_DUMP_TYPE_FILE:
                ret = io_stats_dump_global_to_logfp (this, stats, now,
                                                     interval, args->u.logfp);
        break;
        case IOS_DUMP_TYPE_DICT:
                ret = io_stats_dump_global_to_dict (this, stats, now,
                                                    interval, args->u.dict);
        break;
        default:
                GF_ASSERT (0);
                ret = -1;
        break;
        }
        return ret;
}
