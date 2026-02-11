fuse_setlk_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                int32_t op_ret, int32_t op_errno, struct gf_flock *lock)
{
        fuse_state_t *state = NULL;

        state = frame->root->state;

        if (op_ret == 0) {
                gf_log ("glusterfs-fuse", GF_LOG_TRACE,
                        "%"PRIu64": ERR => 0", frame->root->unique);
                send_fuse_err (this, state->finh, 0);
        } else {
                if (op_errno == ENOSYS) {
                        gf_fuse_lk_enosys_log++;
                        if (!(gf_fuse_lk_enosys_log % GF_UNIVERSAL_ANSWER)) {
                                gf_log ("glusterfs-fuse", GF_LOG_ERROR,
                                        "SETLK not supported. loading "
                                        "'features/posix-locks' on server side "
                                        "will add SETLK support.");
                        }
                } else if (op_errno == EAGAIN) {
                        gf_log ("glusterfs-fuse", GF_LOG_DEBUG,
                                "Returning EAGAIN Flock: "
                                "start=%llu, len=%llu, pid=%llu, lk-owner=%llu",
                                (unsigned long long) lock->l_start,
                                (unsigned long long) lock->l_len,
                                (unsigned long long) lock->l_pid,
                                (unsigned long long) frame->root->lk_owner);

                } else  {
                        gf_log ("glusterfs-fuse", GF_LOG_WARNING,
                                "%"PRIu64": ERR => -1 (%s)",
                                frame->root->unique, strerror (op_errno));
                }

                send_fuse_err (this, state->finh, op_errno);
        }

        free_fuse_state (state);
        STACK_DESTROY (frame->root);

        return 0;
}
