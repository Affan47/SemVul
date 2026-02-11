client_child_up_reopen_done (clnt_fd_ctx_t *fdctx, xlator_t *this)
{
        clnt_conf_t  *conf    = NULL;
        uint64_t     fd_count = 0;

        conf = this->private;

        LOCK (&conf->rec_lock);
        {
                fd_count = --(conf->reopen_fd_count);
        }
        UNLOCK (&conf->rec_lock);

        client_reopen_done (fdctx, this);
        if (fd_count == 0) {
                gf_log (this->name, GF_LOG_INFO,
                        "last fd open'd/lock-self-heal'd - notifying CHILD-UP");
                client_set_lk_version (this);
                client_notify_parents_child_up (this);
        }
}
