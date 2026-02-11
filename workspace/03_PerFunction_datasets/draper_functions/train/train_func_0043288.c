init (xlator_t *this)
{
        int          ret = -1;
        clnt_conf_t *conf = NULL;

        if (this->children) {
                gf_log (this->name, GF_LOG_ERROR,
                        "FATAL: client protocol translator cannot have any "
                        "subvolumes");
                goto out;
        }

        if (!this->parents) {
                gf_log (this->name, GF_LOG_WARNING,
                        "Volume is dangling. ");
        }

        conf = GF_CALLOC (1, sizeof (*conf), gf_client_mt_clnt_conf_t);
        if (!conf)
                goto out;

        pthread_mutex_init (&conf->lock, NULL);
        INIT_LIST_HEAD (&conf->saved_fds);


        conf->lk_version         = 1;
        conf->grace_timer        = NULL;
        conf->grace_timer_needed = _gf_true;

        ret = client_init_grace_timer (this, this->options, conf);
        if (ret)
                goto out;

        LOCK_INIT (&conf->rec_lock);

        conf->last_sent_event = -1;

        this->private = conf;


        ret = build_client_config (this, conf);
        if (ret == -1)
                goto out;

        if (ret) {
                ret = 0;
                goto out;
        }

        this->local_pool = mem_pool_new (clnt_local_t, 64);
        if (!this->local_pool) {
                ret = -1;
                gf_log (this->name, GF_LOG_ERROR,
                        "failed to create local_t's memory pool");
                goto out;
        }

        ret = client_init_rpc (this);
out:
        if (ret)
                this->fini (this);

        return ret;
}
