clnt_fd_lk_reacquire_failed (xlator_t *this, clnt_fd_ctx_t *fdctx,
                             clnt_conf_t *conf)
{
        int      ret = -1;

        GF_VALIDATE_OR_GOTO ("client", this, out);
        GF_VALIDATE_OR_GOTO (this->name, conf, out);
        GF_VALIDATE_OR_GOTO (this->name, fdctx, out);

        pthread_mutex_lock (&conf->lock);
        {
                fdctx->remote_fd     = -1;
                fdctx->lk_heal_state = GF_LK_HEAL_DONE;

                list_add_tail (&fdctx->sfd_pos,
                               &conf->saved_fds);
        }
        pthread_mutex_unlock (&conf->lock);

        ret = 0;
out:
        return ret;
}
