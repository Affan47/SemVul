server_create_resume (call_frame_t *frame, xlator_t *bound_xl)
{
        server_state_t *state = NULL;

        state = CALL_STATE (frame);

        if (state->resolve.op_ret != 0)
                goto err;

        state->loc.inode = inode_new (state->itable);

        state->fd = fd_create (state->loc.inode, frame->root->pid);
        if (!state->fd) {
                gf_log ("server", GF_LOG_ERROR, "fd creation for the inode %s "
                        "failed", state->loc.inode?
                        uuid_utoa (state->loc.inode->gfid):NULL);
                state->resolve.op_ret = -1;
                state->resolve.op_errno = ENOMEM;
                goto err;
        }
        state->fd->flags = state->flags;

        STACK_WIND (frame, server_create_cbk,
                    bound_xl, bound_xl->fops->create,
                    &(state->loc), state->flags, state->mode,
                    state->fd, state->params);

        return 0;
err:
        server_create_cbk (frame, NULL, frame->this, state->resolve.op_ret,
                           state->resolve.op_errno, NULL, NULL, NULL,
                           NULL, NULL);
        return 0;
}
