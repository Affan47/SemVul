afr_symlink (call_frame_t *frame, xlator_t *this,
             const char *linkpath, loc_t *loc, dict_t *params)
{
        afr_private_t * priv  = NULL;
        afr_local_t   * local = NULL;
        call_frame_t  * transaction_frame = NULL;
        int ret = -1;
        int op_ret   = -1;
        int op_errno = 0;

        VALIDATE_OR_GOTO (frame, out);
        VALIDATE_OR_GOTO (this, out);
        VALIDATE_OR_GOTO (this->private, out);

        priv = this->private;

        QUORUM_CHECK(symlink,out);

        transaction_frame = copy_frame (frame);
        if (!transaction_frame) {
                goto out;
        }

        ALLOC_OR_GOTO (local, afr_local_t, out);

        ret = AFR_LOCAL_INIT (local, priv);
        if (ret < 0) {
                op_errno = -ret;
                goto out;
        }

        transaction_frame->local = local;

        loc_copy (&local->loc, loc);

        LOCK (&priv->read_child_lock);
        {
                local->read_child_index = (++priv->read_child_rr)
                        % (priv->child_count);
        }
        UNLOCK (&priv->read_child_lock);

        local->cont.symlink.linkpath = gf_strdup (linkpath);
        if (params)
                local->cont.symlink.params = dict_ref (params);

        local->transaction.fop    = afr_symlink_wind;
        local->transaction.done   = afr_symlink_done;
        local->transaction.unwind = afr_symlink_unwind;

        afr_build_parent_loc (&local->transaction.parent_loc, loc);

        local->transaction.main_frame   = frame;
        local->transaction.basename     = AFR_BASENAME (loc->path);

        afr_transaction (transaction_frame, this, AFR_ENTRY_TRANSACTION);

        op_ret = 0;
out:
        if (op_ret == -1) {
                if (transaction_frame)
                        AFR_STACK_DESTROY (transaction_frame);
                AFR_STACK_UNWIND (symlink, frame, op_ret, op_errno,
                                  NULL, NULL, NULL, NULL);
        }

        return 0;
}
