afr_setxattr (call_frame_t *frame, xlator_t *this,
              loc_t *loc, dict_t *dict, int32_t flags)
{
        afr_private_t * priv  = NULL;
        afr_local_t   * local = NULL;
        call_frame_t   *transaction_frame = NULL;
        int ret = -1;
        int op_ret   = -1;
        int op_errno = 0;

        VALIDATE_OR_GOTO (frame, out);
        VALIDATE_OR_GOTO (this, out);
        VALIDATE_OR_GOTO (this->private, out);

        priv = this->private;

        QUORUM_CHECK(setxattr,out);

        ALLOC_OR_GOTO (local, afr_local_t, out);

        ret = AFR_LOCAL_INIT (local, priv);
        if (ret < 0) {
                op_errno = -ret;
                goto out;
        }

        transaction_frame = copy_frame (frame);
        if (!transaction_frame) {
                goto out;
        }

        transaction_frame->local = local;

        local->op_ret = -1;

        local->cont.setxattr.dict  = dict_ref (dict);
        local->cont.setxattr.flags = flags;

        local->transaction.fop    = afr_setxattr_wind;
        local->transaction.done   = afr_setxattr_done;
        local->transaction.unwind = afr_setxattr_unwind;

        loc_copy (&local->loc, loc);

        local->transaction.main_frame = frame;
        local->transaction.start   = LLONG_MAX - 1;
        local->transaction.len     = 0;

        afr_transaction (transaction_frame, this, AFR_METADATA_TRANSACTION);

        op_ret = 0;
out:
        if (op_ret == -1) {
                if (transaction_frame)
                        AFR_STACK_DESTROY (transaction_frame);
                AFR_STACK_UNWIND (setxattr, frame, op_ret, op_errno);
        }

        return 0;
}
