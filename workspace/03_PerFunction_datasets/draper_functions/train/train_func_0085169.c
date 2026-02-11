delete_rsc_status(lrm_state_t * lrm_state, const char *rsc_id, int call_options,
                  const char *user_name)
{
    char *rsc_xpath = NULL;
    int max = 0;
    int rc = pcmk_ok;

    CRM_CHECK(rsc_id != NULL, return -ENXIO);

    max = strlen(rsc_template) + strlen(rsc_id) + strlen(lrm_state->node_name) + 1;
    rsc_xpath = calloc(1, max);
    snprintf(rsc_xpath, max, rsc_template, lrm_state->node_name, rsc_id);

    rc = cib_internal_op(fsa_cib_conn, CIB_OP_DELETE, NULL, rsc_xpath,
                         NULL, NULL, call_options | cib_xpath, user_name);

    free(rsc_xpath);
    return rc;
}
