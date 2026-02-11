lrm_state_get_rsc_info(lrm_state_t * lrm_state, const char *rsc_id, enum lrmd_call_options options)
{
    if (!lrm_state->conn) {
        return NULL;
    }


    if (is_remote_lrmd_ra(NULL, NULL, rsc_id)) {
        return remote_ra_get_rsc_info(lrm_state, rsc_id);
    }

    return ((lrmd_t *) lrm_state->conn)->cmds->get_rsc_info(lrm_state->conn, rsc_id, options);
}
