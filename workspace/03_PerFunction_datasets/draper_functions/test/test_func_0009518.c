server_fsetattr_resume (call_frame_t *frame, xlator_t *bound_xl)
{
        server_state_t *state = NULL;

        state = CALL_STATE (frame);

        if (state->resolve.op_ret != 0)
                goto err;

        STACK_WIND (frame, server_fsetattr_cbk,
                    bound_xl, bound_xl->fops->fsetattr,
                    state->fd, &state->stbuf, state->valid, state->xdata);
        return 0;
err:
        server_fsetattr_cbk (frame, NULL, frame->this, state->resolve.op_ret,
                             state->resolve.op_errno, NULL, NULL, NULL);

        return 0;
}
