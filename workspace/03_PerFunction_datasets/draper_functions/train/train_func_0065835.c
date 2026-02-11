get_lrm_resource(lrm_state_t * lrm_state, xmlNode * resource, xmlNode * op_msg, gboolean do_create)
{
    lrmd_rsc_info_t *rsc = NULL;
    const char *id = ID(resource);
    const char *type = crm_element_value(resource, XML_ATTR_TYPE);
    const char *class = crm_element_value(resource, XML_AGENT_ATTR_CLASS);
    const char *provider = crm_element_value(resource, XML_AGENT_ATTR_PROVIDER);
    const char *long_id = crm_element_value(resource, XML_ATTR_ID_LONG);

    crm_trace("Retrieving %s from the LRM.", id);
    CRM_CHECK(id != NULL, return NULL);

    rsc = lrm_state_get_rsc_info(lrm_state, id, 0);

    if (!rsc && long_id) {
        rsc = lrm_state_get_rsc_info(lrm_state, long_id, 0);
    }

    if (!rsc && do_create) {
        CRM_CHECK(class != NULL, return NULL);
        CRM_CHECK(type != NULL, return NULL);

        crm_trace("Adding rsc %s before operation", id);

        lrm_state_register_rsc(lrm_state, id, class, provider, type, lrmd_opt_drop_recurring);

        rsc = lrm_state_get_rsc_info(lrm_state, id, 0);

        if (!rsc) {
            fsa_data_t *msg_data = NULL;

            crm_err("Could not add resource %s to LRM", id);
            register_fsa_error(C_FSA_INTERNAL, I_FAIL, NULL);
        }
    }

    return rsc;
}
