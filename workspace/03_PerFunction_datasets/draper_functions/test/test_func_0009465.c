client_post_handshake (call_frame_t *frame, xlator_t *this)
{
        clnt_conf_t            *conf = NULL;
        clnt_fd_ctx_t          *tmp = NULL;
        clnt_fd_ctx_t          *fdctx = NULL;
        struct list_head        reopen_head;

        int count = 0;

        if (!this || !this->private)
                goto out;

        conf = this->private;
        INIT_LIST_HEAD (&reopen_head);

        pthread_mutex_lock (&conf->lock);
        {
                list_for_each_entry_safe (fdctx, tmp, &conf->saved_fds,
                                          sfd_pos) {
                        if (fdctx->remote_fd != -1)
                                continue;

                        list_del_init (&fdctx->sfd_pos);
                        list_add_tail (&fdctx->sfd_pos, &reopen_head);
                        count++;
                }
        }
        pthread_mutex_unlock (&conf->lock);


        if (count > 0) {
                gf_log (this->name, GF_LOG_INFO,
                        "%d fds open - Delaying child_up until they are re-opened",
                        count);
                client_save_number_fds (conf, count);

                list_for_each_entry_safe (fdctx, tmp, &reopen_head, sfd_pos) {
                        list_del_init (&fdctx->sfd_pos);

                        if (fdctx->is_dir)
                                protocol_client_reopendir (this, fdctx);
                        else
                                protocol_client_reopen (this, fdctx);
                }
        } else {
                gf_log (this->name, GF_LOG_DEBUG,
                        "no open fds - notifying all parents child up");
                client_notify_parents_child_up (this);
        }
out:
        return 0;
}
