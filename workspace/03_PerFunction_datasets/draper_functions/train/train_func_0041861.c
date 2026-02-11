orte_rml_oob_send_nb(orte_process_name_t* peer,
                         struct iovec* iov,
                         int count,
                         orte_rml_tag_t tag,
                         orte_rml_callback_fn_t cbfunc,
                         void* cbdata)
{
    orte_rml_send_request_t *req;

    OPAL_OUTPUT_VERBOSE((1, orte_rml_base_framework.framework_output,
                         "%s rml_send to peer %s at tag %d",
                         ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                         ORTE_NAME_PRINT(peer), tag));

    if (ORTE_RML_TAG_INVALID == tag) {

        ORTE_ERROR_LOG(ORTE_ERR_BAD_PARAM);
        return ORTE_ERR_BAD_PARAM;
    }


    req = OBJ_NEW(orte_rml_send_request_t);
    req->post.peer = *peer;
    req->post.iov = iov;
    req->post.count = count;
    req->post.tag = tag;
    req->post.cbfunc.iov = cbfunc;
    req->post.cbdata = cbdata;

    opal_event_set(orte_event_base, &req->ev, -1, OPAL_EV_WRITE, send_msg, req);
    opal_event_set_priority(&req->ev, ORTE_MSG_PRI);
    opal_event_active(&req->ev, OPAL_EV_WRITE, 1);

    return ORTE_SUCCESS;
}
