iot_priv_dump (xlator_t *this)
{
        iot_conf_t     *conf   =   NULL;
        char           key_prefix[GF_DUMP_MAX_BUF_LEN];

        if (!this)
                return 0;

        conf = this->private;
        if (!conf)
                return 0;

        snprintf (key_prefix, GF_DUMP_MAX_BUF_LEN, "%s.%s", this->type,
                  this->name);

        gf_proc_dump_add_section(key_prefix);

        gf_proc_dump_write("maximum_threads_count", "%d", conf->max_count);
        gf_proc_dump_write("current_threads_count", "%d", conf->curr_count);
        gf_proc_dump_write("sleep_count", "%d", conf->sleep_count);
        gf_proc_dump_write("idle_time", "%d", conf->idle_time);
        gf_proc_dump_write("stack_size", "%zd", conf->stack_size);
        gf_proc_dump_write("high_priority_threads", "%d",
                           conf->ac_iot_limit[IOT_PRI_HI]);
        gf_proc_dump_write("normal_priority_threads", "%d",
                           conf->ac_iot_limit[IOT_PRI_NORMAL]);
        gf_proc_dump_write("low_priority_threads", "%d",
                           conf->ac_iot_limit[IOT_PRI_LO]);
        gf_proc_dump_write("least_priority_threads", "%d",
                           conf->ac_iot_limit[IOT_PRI_LEAST]);

	gf_proc_dump_write("cached least rate", "%u",
			   conf->throttle.cached_rate);
	gf_proc_dump_write("least rate limit", "%u", conf->throttle.rate_limit);

        return 0;
}
