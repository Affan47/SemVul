remote_ra_cleanup(lrm_state_t * lrm_state)
{
    remote_ra_data_t *ra_data = lrm_state->remote_ra_data;

    if (!ra_data) {
        return;
    }

    if (ra_data->cmds) {
        g_list_free_full(ra_data->cmds, free_cmd);
    }

    if (ra_data->recurring_cmds) {
        g_list_free_full(ra_data->recurring_cmds, free_cmd);
    }
    mainloop_destroy_trigger(ra_data->work);
    free(ra_data);
    lrm_state->remote_ra_data = NULL;
}
