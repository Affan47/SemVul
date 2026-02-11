afr_readlink_cbk (call_frame_t *frame, void *cookie,
                  xlator_t *this, int32_t op_ret, int32_t op_errno,
                  const char *buf, struct iatt *sbuf)
{
        afr_private_t * priv                  = NULL;
        afr_local_t *   local                 = NULL;
        xlator_t **     children              = NULL;
        int             unwind                = 1;
        int32_t         *last_index           = NULL;
        int32_t         next_call_child       = -1;
        int32_t         read_child            = -1;
        int32_t         *fresh_children        = NULL;

        priv     = this->private;
        children = priv->children;

        local = frame->local;

        read_child = (long) cookie;

        if (op_ret == -1) {
                last_index = &local->cont.readlink.last_index;
                fresh_children = local->fresh_children;
                next_call_child = afr_next_call_child (fresh_children,
                                                       local->child_up,
                                                       priv->child_count,
                                                       last_index, read_child);
                if (next_call_child < 0)
                        goto out;

                unwind = 0;
                STACK_WIND_COOKIE (frame, afr_readlink_cbk,
                                   (void *) (long) read_child,
                                   children[next_call_child],
                                   children[next_call_child]->fops->readlink,
                                   &local->loc,
                                   local->cont.readlink.size);
        }

out:
        if (unwind) {
                AFR_STACK_UNWIND (readlink, frame, op_ret, op_errno, buf, sbuf);
        }

        return 0;
}
