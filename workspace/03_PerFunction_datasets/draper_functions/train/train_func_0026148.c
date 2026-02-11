init (xlator_t *this)
{
        int ret = -1;
        index_priv_t *priv = NULL;
        pthread_t thread;
        pthread_attr_t  w_attr;
        gf_boolean_t    mutex_inited = _gf_false;
        gf_boolean_t    cond_inited  = _gf_false;
        gf_boolean_t    attr_inited  = _gf_false;

	if (!this->children || this->children->next) {
		gf_log (this->name, GF_LOG_ERROR,
			"'index' not configured with exactly one child");
                goto out;
	}

	if (!this->parents) {
		gf_log (this->name, GF_LOG_WARNING,
			"dangling volume. check volfile ");
	}

        priv = GF_CALLOC (1, sizeof (*priv), gf_index_mt_priv_t);
        if (!priv)
                goto out;

        LOCK_INIT (&priv->lock);
        if ((ret = pthread_cond_init(&priv->cond, NULL)) != 0) {
                gf_log (this->name, GF_LOG_ERROR,
                        "pthread_cond_init failed (%d)", ret);
                goto out;
        }
        cond_inited = _gf_true;

        if ((ret = pthread_mutex_init(&priv->mutex, NULL)) != 0) {
                gf_log (this->name, GF_LOG_ERROR,
                        "pthread_mutex_init failed (%d)", ret);
                goto out;
        }
        mutex_inited = _gf_true;

        if ((ret = pthread_attr_init (&w_attr)) != 0) {
                gf_log (this->name, GF_LOG_ERROR,
                        "pthread_attr_init failed (%d)", ret);
                goto out;
        }
        attr_inited = _gf_true;

        ret = pthread_attr_setstacksize (&w_attr, INDEX_THREAD_STACK_SIZE);
        if (ret == EINVAL) {
                gf_log (this->name, GF_LOG_WARNING,
                        "Using default thread stack size");
        }
        GF_OPTION_INIT ("index-base", priv->index_basepath, path, out);
        uuid_generate (priv->index);
        uuid_generate (priv->xattrop_vgfid);
        INIT_LIST_HEAD (&priv->callstubs);

        this->private = priv;
        ret = pthread_create (&thread, &w_attr, index_worker, this);
        if (ret) {
                gf_log (this->name, GF_LOG_WARNING, "Failed to create "
                        "worker thread, aborting");
                goto out;
        }
        ret = 0;
out:
        if (ret) {
                if (cond_inited)
                        pthread_cond_destroy (&priv->cond);
                if (mutex_inited)
                        pthread_mutex_destroy (&priv->mutex);
                if (priv)
                        GF_FREE (priv);
                this->private = NULL;
        }
        if (attr_inited)
                pthread_attr_destroy (&w_attr);
        return ret;
}
