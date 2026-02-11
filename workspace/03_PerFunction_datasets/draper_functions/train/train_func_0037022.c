afr_symlink (call_frame_t *frame, xlator_t *this,
             const char *linkpath, loc_t *loc, mode_t umask, dict_t *params)
{
        afr_private_t           *priv                   = NULL;
        afr_local_t             *local                  = NULL;
        afr_internal_lock_t     *int_lock               = NULL;
        call_frame_t            *transaction_frame      = NULL;
        int                     ret                     = -1;
        int                     op_errno                = 0;

        VALIDATE_OR_GOTO (frame, out);
        VALIDATE_OR_GOTO (this, out);
        VALIDATE_OR_GOTO (this->private, out);

        priv = this->private;

        QUORUM_CHECK(symlink,out);

        transaction_frame = copy_frame (frame);
        if (!transaction_frame) {
                op_errno = ENOMEM;
                goto out;
        }

        AFR_LOCAL_ALLOC_OR_GOTO (transaction_frame->local, out);
        local = transaction_frame->local;

        ret = afr_local_init (local, priv, &op_errno);
        if (ret < 0)
                goto out;

        loc_copy (&local->loc, loc);

        LOCK (&priv->read_child_lock);
        {
                local->read_child_index = (++priv->read_child_rr)
                        % (priv->child_count);
        }
        UNLOCK (&priv->read_child_lock);

        local->cont.symlink.linkpath = gf_strdup (linkpath);
        local->umask = umask;
        if (params)
                local->xdata_req = dict_ref (params);

        local->transaction.fop    = afr_symlink_wind;
        local->transaction.done   = afr_symlink_done;
        local->transaction.unwind = afr_symlink_unwind;

        ret = afr_build_parent_loc (&local->transaction.parent_loc, loc,
                                    &op_errno);
        if (ret)
                goto out;

        local->transaction.main_frame   = frame;
        local->transaction.basename     = AFR_BASENAME (loc->path);
        int_lock = &local->internal_lock;

        int_lock->lockee_count = 0;
        ret = afr_init_entry_lockee (&int_lock->lockee[0], local,
                                     &local->transaction.parent_loc,
                                     local->transaction.basename,
                                     priv->child_count);
        if (ret)
                goto out;

        int_lock->lockee_count++;
        ret = afr_transaction (transaction_frame, this, AFR_ENTRY_TRANSACTION);
        if (ret < 0) {
            op_errno = -ret;
            goto out;
        }

        ret = 0;
out:
        if (ret  < 0) {
                if (transaction_frame)
                        AFR_STACK_DESTROY (transaction_frame);
                AFR_STACK_UNWIND (symlink, frame, -1, op_errno,
                                  NULL, NULL, NULL, NULL, NULL);
        }

        return 0;
}
