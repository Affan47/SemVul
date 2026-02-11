server_flush_resume (call_frame_t *frame, xlator_t *bound_xl)
{
        server_state_t    *state = NULL;

        state = CALL_STATE (frame);

        if (state->resolve.op_ret != 0)
                goto err;

        STACK_WIND (frame, server_flush_cbk,
                    bound_xl, bound_xl->fops->flush, state->fd);
        return 0;
err:
        server_flush_cbk (frame, NULL, frame->this, state->resolve.op_ret,
                          state->resolve.op_errno);

        return 0;
}
