stripe_statfs (call_frame_t *frame, xlator_t *this, loc_t *loc)
{
        stripe_local_t   *local = NULL;
        xlator_list_t    *trav = NULL;
        stripe_private_t *priv = NULL;
        int32_t           op_errno = EINVAL;

        VALIDATE_OR_GOTO (frame, err);
        VALIDATE_OR_GOTO (this, err);
        VALIDATE_OR_GOTO (loc, err);

        trav = this->children;
        priv = this->private;


        local = GF_CALLOC (1, sizeof (stripe_local_t),
                           gf_stripe_mt_stripe_local_t);
        if (!local) {
                op_errno = ENOMEM;
                goto err;
        }
        local->op_ret = -1;
        local->op_errno = ENOTCONN;
        frame->local = local;

        local->call_count = priv->child_count;
        while (trav) {
                STACK_WIND (frame, stripe_statfs_cbk, trav->xlator,
                            trav->xlator->fops->statfs, loc);
                trav = trav->next;
        }

        return 0;
err:
        STRIPE_STACK_UNWIND (statfs, frame, -1, op_errno, NULL);
        return 0;
}
