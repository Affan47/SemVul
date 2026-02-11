client3_3_releasedir (call_frame_t *frame, xlator_t *this,
                      void *data)
{
        clnt_conf_t         *conf        = NULL;
        clnt_fd_ctx_t       *fdctx       = NULL;
        clnt_args_t         *args        = NULL;
        int64_t              remote_fd   = -1;

        if (!this || !data)
                goto out;

        args = data;
        conf = this->private;

        pthread_mutex_lock (&conf->lock);
        {
                fdctx = this_fd_del_ctx (args->fd, this);
                if (fdctx != NULL) {
                        remote_fd = fdctx->remote_fd;


                        if (remote_fd != -1)
                                list_del_init (&fdctx->sfd_pos);

                        fdctx->released = 1;
                }
        }
        pthread_mutex_unlock (&conf->lock);

        if (remote_fd != -1)
                client_fdctx_destroy (this, fdctx);
out:

        return 0;
}
