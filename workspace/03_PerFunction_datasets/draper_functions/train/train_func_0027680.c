server_entrylk_resume (call_frame_t *frame, xlator_t *bound_xl)
{
        server_state_t *state = NULL;

        state = CALL_STATE (frame);

        if (state->resolve.op_ret != 0)
                goto err;

        STACK_WIND (frame, server_entrylk_cbk,
                    bound_xl, bound_xl->fops->entrylk,
                    state->volume, &state->loc, state->name,
                    state->cmd, state->type, state->xdata);
        return 0;
err:
        server_entrylk_cbk (frame, NULL, frame->this, state->resolve.op_ret,
                            state->resolve.op_errno, NULL);
        return 0;
}
