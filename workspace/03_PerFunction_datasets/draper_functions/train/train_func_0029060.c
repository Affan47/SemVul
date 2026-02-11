mq_inode_creation_done (call_frame_t *frame, void *cookie, xlator_t *this,
                        int32_t op_ret, int32_t op_errno)
{
        quota_local_t *local = NULL;

        if (frame == NULL)
                return 0;

        local = frame->local;

        if (local != NULL) {
                mq_initiate_quota_txn (this, &local->loc);
        }

        QUOTA_STACK_DESTROY (frame, this);

        return 0;
}
