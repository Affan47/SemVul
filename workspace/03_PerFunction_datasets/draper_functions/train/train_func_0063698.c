_gf_server_log_setxattr_failure (dict_t *d, char *k, data_t *v,
                                 void *tmp)
{
        server_state_t *state = NULL;
        call_frame_t   *frame = NULL;

        frame = tmp;
        state = CALL_STATE(frame);

        gf_log (THIS->name, GF_LOG_INFO,
                "%"PRId64": SETXATTR %s (%s) ==> %s",
                frame->root->unique, state->loc.path,
                uuid_utoa (state->resolve.gfid), k);
        return 0;
}
