stripe_unlink (call_frame_t *frame, xlator_t *this, loc_t *loc,
               int xflag, dict_t *xdata)
{
        xlator_list_t    *trav = NULL;
        stripe_local_t   *local = NULL;
        stripe_private_t *priv = NULL;
        int32_t           op_errno = EINVAL;

        VALIDATE_OR_GOTO (frame, err);
        VALIDATE_OR_GOTO (this, err);
        VALIDATE_OR_GOTO (loc, err);
        VALIDATE_OR_GOTO (loc->path, err);
        VALIDATE_OR_GOTO (loc->inode, err);

        priv = this->private;
        trav = this->children;

        if (priv->first_child_down) {
                op_errno = ENOTCONN;
                goto err;
        }


        if (priv->nodes_down) {
                op_errno = ENOTCONN;
                goto err;
        }


        local = mem_get0 (this->local_pool);
        if (!local) {
                op_errno = ENOMEM;
                goto err;
        }
        local->op_ret = -1;
        loc_copy (&local->loc, loc);
        local->xflag = xflag;

        if (xdata)
            local->xdata = dict_ref (xdata);

        frame->local = local;
        local->call_count = priv->child_count;
        trav = trav->next;

        while (trav) {
                STACK_WIND (frame, stripe_unlink_cbk,
                            trav->xlator, trav->xlator->fops->unlink,
                            loc, xflag, xdata);
                trav = trav->next;
        }

        return 0;
err:
        STRIPE_STACK_UNWIND (unlink, frame, -1, op_errno, NULL, NULL, NULL);
        return 0;
}
