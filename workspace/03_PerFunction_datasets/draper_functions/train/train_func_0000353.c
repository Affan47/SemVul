afr_fsetxattr (call_frame_t *frame, xlator_t *this,
               fd_t *fd, dict_t *dict, int32_t flags)
{
        afr_private_t    *priv              = NULL;
        afr_local_t      *local             = NULL;
        call_frame_t     *transaction_frame = NULL;
        int               ret               = -1;
        int               op_errno          = EINVAL;
        data_pair_t      *trav              = NULL;

        VALIDATE_OR_GOTO (frame, out);
        VALIDATE_OR_GOTO (this, out);
        VALIDATE_OR_GOTO (this->private, out);

        GF_IF_INTERNAL_XATTR_GOTO ("trusted.afr.*", dict,
                                   trav, op_errno, out);

        GF_IF_INTERNAL_XATTR_GOTO ("trusted.glusterfs.afr.*", dict,
                                   trav, op_errno, out);

        if (ret)
                goto out;

        priv = this->private;

        QUORUM_CHECK(fsetxattr,out);

        ALLOC_OR_GOTO (local, afr_local_t, out);

        ret = afr_local_init (local, priv, &op_errno);
        if (ret < 0)
                goto out;

        transaction_frame = copy_frame (frame);
        if (!transaction_frame) {
                goto out;
        }

        transaction_frame->local = local;

        local->op_ret = -1;

        local->cont.fsetxattr.dict  = dict_ref (dict);
        local->cont.fsetxattr.flags = flags;

        local->transaction.fop    = afr_fsetxattr_wind;
        local->transaction.done   = afr_fsetxattr_done;
        local->transaction.unwind = afr_fsetxattr_unwind;

        local->fd                 = fd_ref (fd);

        local->transaction.main_frame = frame;
        local->transaction.start  = LLONG_MAX - 1;
        local->transaction.len    = 0;

        afr_transaction (transaction_frame, this, AFR_METADATA_TRANSACTION);

        ret = 0;
out:
        if (ret < 0) {
                if (transaction_frame)
                        AFR_STACK_DESTROY (transaction_frame);
                AFR_STACK_UNWIND (fsetxattr, frame, -1, op_errno);
        }

        return 0;
}
