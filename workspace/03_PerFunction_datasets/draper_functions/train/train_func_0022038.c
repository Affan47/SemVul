stripe_fsetattr (call_frame_t *frame, xlator_t *this, fd_t *fd,
                 struct iatt *stbuf, int32_t valid)
{
        stripe_local_t   *local = NULL;
        stripe_private_t *priv = NULL;
        xlator_list_t    *trav = NULL;
        int32_t           op_errno = EINVAL;

        VALIDATE_OR_GOTO (frame, err);
        VALIDATE_OR_GOTO (this, err);
        VALIDATE_OR_GOTO (fd, err);
        VALIDATE_OR_GOTO (fd->inode, err);

        priv = this->private;
        trav = this->children;


        local = GF_CALLOC (1, sizeof (stripe_local_t),
                           gf_stripe_mt_stripe_local_t);
        if (!local) {
                op_errno = ENOMEM;
                goto err;
        }
        local->op_ret = -1;
        frame->local = local;
        local->call_count = priv->child_count;

        while (trav) {
                STACK_WIND (frame, stripe_setattr_cbk, trav->xlator,
                            trav->xlator->fops->fsetattr, fd, stbuf, valid);
                trav = trav->next;
        }

        return 0;
err:
        STRIPE_STACK_UNWIND (fsetattr, frame, -1, op_errno, NULL, NULL);
        return 0;
}
