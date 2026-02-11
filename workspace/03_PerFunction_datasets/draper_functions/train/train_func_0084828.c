init (xlator_t *this)
{
        struct ios_conf    *conf = NULL;
        char               *sys_log_str = NULL;
        int                 sys_log_level = -1;
        char               *log_str = NULL;
        int                 log_level = -1;
        int                 ret = -1;

        if (!this)
                return -1;

        if (!this->children) {
                gf_log (this->name, GF_LOG_ERROR,
                        "io_stats translator requires atleast one subvolume");
                return -1;
        }

        if (!this->parents) {


                gf_log (this->name, GF_LOG_DEBUG,
                        "dangling volume. check volfile ");
        }

        conf = GF_CALLOC (1, sizeof(*conf), gf_io_stats_mt_ios_conf);

        if (!conf) {
                gf_log (this->name, GF_LOG_ERROR,
                        "Out of memory.");
                return -1;
        }

        LOCK_INIT (&conf->lock);

        gettimeofday (&conf->cumulative.started_at, NULL);
        gettimeofday (&conf->incremental.started_at, NULL);

        ret = ios_init_top_stats (conf);
        if (ret)
                return -1;

        GF_OPTION_INIT ("dump-fd-stats", conf->dump_fd_stats, bool, out);

        GF_OPTION_INIT ("count-fop-hits", conf->count_fop_hits, bool, out);

        GF_OPTION_INIT ("latency-measurement", conf->measure_latency,
                          bool, out);

        GF_OPTION_INIT ("sys-log-level", sys_log_str, str, out);
        if (sys_log_str) {
                sys_log_level = glusterd_check_log_level (sys_log_str);
                set_sys_log_level (sys_log_level);
        }

        GF_OPTION_INIT ("log-level", log_str, str, out);
        if (log_str) {
                log_level = glusterd_check_log_level (log_str);
                gf_log_set_loglevel (log_level);
        }

        this->private = conf;
        ret = 0;
out:
        return ret;
}
