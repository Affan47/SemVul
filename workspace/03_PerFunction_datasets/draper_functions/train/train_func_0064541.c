afr_fstat_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
               int32_t op_ret, int32_t op_errno, struct iatt *buf,
               dict_t *xdata)
{
        afr_private_t   *priv           = NULL;
        afr_local_t     *local          = NULL;
        xlator_t        **children      = NULL;
        int             unwind          = 1;
        int32_t         *last_index     = NULL;
        int32_t         next_call_child = -1;
        int32_t         read_child      = -1;
        int32_t         *fresh_children  = NULL;

        priv     = this->private;
        children = priv->children;

        local = frame->local;

        read_child = (long) cookie;

        if (op_ret == -1) {
                last_index = &local->cont.fstat.last_index;
                fresh_children = local->fresh_children;
                next_call_child = afr_next_call_child (fresh_children,
                                                       local->child_up,
                                                       priv->child_count,
                                                       last_index, read_child);
                if (next_call_child < 0)
                        goto out;

                unwind = 0;

                STACK_WIND_COOKIE (frame, afr_fstat_cbk,
                                   (void *) (long) read_child,
                                   children[next_call_child],
                                   children[next_call_child]->fops->fstat,
                                   local->fd, NULL);
        }

out:
        if (unwind) {
                AFR_STACK_UNWIND (fstat, frame, op_ret, op_errno, buf, xdata);
        }

        return 0;
}
