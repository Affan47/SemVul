fini (xlator_t *this)
{
        glusterd_conf_t *conf = NULL;
        if (!this || !this->private)
                goto out;

        conf = this->private;
        FREE (conf->pmap);
        if (conf->handle)
                gf_store_handle_destroy (conf->handle);
        glusterd_sm_tr_log_delete (&conf->op_sm_log);
        GF_FREE (conf);
        this->private = NULL;
out:
        return;
}
