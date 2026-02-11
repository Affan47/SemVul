fuse_setlk_resume (fuse_state_t *state)
{
        gf_log ("glusterfs-fuse", GF_LOG_TRACE,
                "%"PRIu64": SETLK%s %p", state->finh->unique,
                state->finh->opcode == FUSE_SETLK ? "" : "W", state->fd);

        FUSE_FOP (state, fuse_setlk_cbk, GF_FOP_LK, lk, state->fd,
                  state->finh->opcode == FUSE_SETLK ? F_SETLK : F_SETLKW,
                  &state->lk_lock);
}
