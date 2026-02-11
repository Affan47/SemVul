lrmd_send_command(lrmd_t * lrmd, const char *op, xmlNode * data, xmlNode ** output_data, int timeout,
                  enum lrmd_call_options options, gboolean expect_reply)
{
    int rc = pcmk_ok;
    int reply_id = -1;
    lrmd_private_t *native = lrmd->private;
    xmlNode *op_msg = NULL;
    xmlNode *op_reply = NULL;

    if (!lrmd_api_is_connected(lrmd)) {
        return -ENOTCONN;
    }

    if (op == NULL) {
        crm_err("No operation specified");
        return -EINVAL;
    }

    CRM_CHECK(native->token != NULL,;
        );
    crm_trace("sending %s op to lrmd", op);

    op_msg = lrmd_create_op(native->token, op, data, options);

    if (op_msg == NULL) {
        return -EINVAL;
    }

    crm_xml_add_int(op_msg, F_LRMD_TIMEOUT, timeout);

    if (expect_reply) {
        rc = lrmd_send_xml(lrmd, op_msg, timeout, &op_reply);
    } else {
        rc = lrmd_send_xml_no_reply(lrmd, op_msg);
        goto done;
    }

    if (rc < 0) {
        crm_perror(LOG_ERR, "Couldn't perform %s operation (timeout=%d): %d", op, timeout, rc);
        rc = -ECOMM;
        goto done;
    }

    rc = pcmk_ok;
    crm_element_value_int(op_reply, F_LRMD_CALLID, &reply_id);
    crm_trace("%s op reply received", op);
    if (crm_element_value_int(op_reply, F_LRMD_RC, &rc) != 0) {
        rc = -ENOMSG;
        goto done;
    }

    crm_log_xml_trace(op_reply, "Reply");

    if (output_data) {
        *output_data = op_reply;
        op_reply = NULL;
    }

  done:
    if (lrmd_api_is_connected(lrmd) == FALSE) {
        crm_err("LRMD disconnected");
    }

    free_xml(op_msg);
    free_xml(op_reply);
    return rc;
}
