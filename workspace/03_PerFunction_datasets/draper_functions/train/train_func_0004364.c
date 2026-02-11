init (xlator_t *this)
{
        wb_conf_t *conf    = NULL;
        int32_t    ret     = -1;

        if ((this->children == NULL)
            || this->children->next) {
                gf_log (this->name, GF_LOG_ERROR,
                        "FATAL: write-behind (%s) not configured with exactly "
                        "one child", this->name);
                goto out;
        }

        if (this->parents == NULL) {
                gf_log (this->name, GF_LOG_WARNING,
                        "dangling volume. check volfile");
        }

        conf = GF_CALLOC (1, sizeof (*conf), gf_wb_mt_wb_conf_t);
        if (conf == NULL) {
                goto out;
        }

        GF_OPTION_INIT("enable-O_SYNC", conf->enable_O_SYNC, bool, out);


        conf->aggregate_size = WB_AGGREGATE_SIZE;

        GF_OPTION_INIT("disable-for-first-nbytes", conf->disable_till, size,
                       out);


        GF_OPTION_INIT ("cache-size", conf->window_size, size, out);

        if (!conf->window_size && conf->aggregate_size) {
                gf_log (this->name, GF_LOG_WARNING,
                        "setting window-size to be equal to "
                        "aggregate-size(%"PRIu64")",
                        conf->aggregate_size);
                conf->window_size = conf->aggregate_size;
        }

        if (conf->window_size < conf->aggregate_size) {
                gf_log (this->name, GF_LOG_ERROR,
                        "aggregate-size(%"PRIu64") cannot be more than "
                        "window-size(%"PRIu64")", conf->aggregate_size,
                        conf->window_size);
                goto out;
        }


        GF_OPTION_INIT ("flush-behind", conf->flush_behind, bool, out);

        GF_OPTION_INIT ("enable-trickling-writes", conf->enable_trickling_writes,
                        bool, out);

        this->private = conf;
        ret = 0;

out:
        if (ret) {
                if (conf)
                        GF_FREE (conf);
        }
        return ret;
}
