afr_create_done (call_frame_t *frame, xlator_t *this)
{
        afr_local_t * local = NULL;

        local = frame->local;

        local->transaction.unwind (frame, this);

        AFR_STACK_DESTROY (frame);

        return 0;
}
