cimd2_destroy(PrivData *pdata)
{
    int discarded;

    if (pdata == NULL)
        return;

    octstr_destroy(pdata->host);
    octstr_destroy(pdata->username);
    octstr_destroy(pdata->password);
    octstr_destroy(pdata->inbuffer);
    octstr_destroy(pdata->my_number);

    discarded = gwlist_len(pdata->received);
    if (discarded > 0)
        warning(0, "CIMD2[%s]: discarded %d received messages",
                octstr_get_cstr(pdata->conn->id),
                discarded);

    gwlist_destroy(pdata->received, msg_destroy_item);
    gwlist_destroy(pdata->outgoing_queue, NULL);
    gwlist_destroy(pdata->stopped, NULL);

    gw_free(pdata);
}
