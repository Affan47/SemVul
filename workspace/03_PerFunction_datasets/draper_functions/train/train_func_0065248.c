do_cl_join_query(long long action,
                 enum crmd_fsa_cause cause,
                 enum crmd_fsa_state cur_state,
                 enum crmd_fsa_input current_input, fsa_data_t * msg_data)
{
    xmlNode *req = create_request(CRM_OP_JOIN_ANNOUNCE, NULL, NULL,
                                  CRM_SYSTEM_DC, CRM_SYSTEM_CRMD, NULL);

    sleep(1);
    update_dc(NULL);
    crm_debug("Querying for a DC");
    send_cluster_message(NULL, crm_msg_crmd, req, FALSE);
    free_xml(req);
}
