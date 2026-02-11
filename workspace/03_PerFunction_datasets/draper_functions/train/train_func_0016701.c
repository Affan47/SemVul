conndata_destroy(ConnData *conndata)
{
    if (conndata == NULL)
        return;
    if (conndata->http_ref)
        http_caller_destroy(conndata->http_ref);
    if (conndata->success_regex)
        gw_regex_destroy(conndata->success_regex);
    if (conndata->permfail_regex)
        gw_regex_destroy(conndata->permfail_regex);
    if (conndata->tempfail_regex)
        gw_regex_destroy(conndata->tempfail_regex);
    if (conndata->generic_foreign_id_regex)
        gw_regex_destroy(conndata->generic_foreign_id_regex);
    fieldmap_destroy(conndata->fieldmap);
    octstr_destroy(conndata->allow_ip);
    octstr_destroy(conndata->send_url);
    octstr_destroy(conndata->dlr_url);
    octstr_destroy(conndata->username);
    octstr_destroy(conndata->password);
    octstr_destroy(conndata->proxy);
    octstr_destroy(conndata->system_id);
    octstr_destroy(conndata->alt_charset);
    counter_destroy(conndata->open_sends);
    gwlist_destroy(conndata->msg_to_send, NULL);
    if (conndata->max_pending_sends)
        semaphore_destroy(conndata->max_pending_sends);

    gw_free(conndata);
}
