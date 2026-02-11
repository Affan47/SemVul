afr_writev_handle_short_writes (call_frame_t *frame, xlator_t *this)
{
        afr_local_t   *local = NULL;
        afr_private_t *priv  = NULL;
        int           i      = 0;

        local = frame->local;
        priv = this->private;


        for (i = 0; i < priv->child_count; i++) {
                if ((!local->replies[i].valid) ||
                    (local->replies[i].op_ret == -1))
                        continue;

                if (local->replies[i].op_ret < local->op_ret)
                        afr_transaction_fop_failed(frame, this, i);
        }
}
