clnt_fd_lk_local_mark_error (xlator_t *this,
                             clnt_fd_lk_local_t *local)
{
        int32_t       ret   = -1;
        clnt_conf_t  *conf  = NULL;
        gf_boolean_t  error = _gf_false;

        GF_VALIDATE_OR_GOTO ("client", this, out);
        GF_VALIDATE_OR_GOTO (this->name, local, out);

        conf = (clnt_conf_t *) this->private;

        LOCK (&local->lock);
        {
                error        = local->error;
                local->error = _gf_true;
        }
        UNLOCK (&local->lock);

        if (!error)
                clnt_reacquire_lock_error (this, local->fdctx, conf);
        ret = 0;
out:
        return ret;
}
