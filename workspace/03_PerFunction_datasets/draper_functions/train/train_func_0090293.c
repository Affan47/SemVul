lrm_state_ipc_connect(lrm_state_t * lrm_state)
{
    int ret;

    if (!lrm_state->conn) {
        lrm_state->conn = lrmd_api_new();
        ((lrmd_t *) lrm_state->conn)->cmds->set_callback(lrm_state->conn, lrm_op_callback);
    }

    ret = ((lrmd_t *) lrm_state->conn)->cmds->connect(lrm_state->conn, CRM_SYSTEM_CRMD, NULL);

    if (ret != pcmk_ok) {
        lrm_state->num_lrm_register_fails++;
    } else {
        lrm_state->num_lrm_register_fails = 0;
    }

    return ret;
}
