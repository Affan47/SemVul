make_unit_push_request(WAPEvent *e)
{
    WAPEvent *wsp_event;
    List *push_headers;
    Octstr *smsc_id;
    Octstr *dlr_url;
    Octstr *smsbox_id;
    Octstr *push_body;
    Octstr *service_name;

    gw_assert(e->type == Po_Unit_Push_Req);
    gw_assert(e->u.Po_Unit_Push_Req.addr_tuple);
    gw_assert(e->u.Po_Unit_Push_Req.service_name);

    smsc_id = octstr_duplicate(e->u.Po_Unit_Push_Req.smsc_id);
    dlr_url = octstr_duplicate(e->u.Po_Unit_Push_Req.dlr_url);
    smsbox_id = octstr_duplicate(e->u.Po_Unit_Push_Req.smsbox_id);
    push_body = octstr_duplicate(e->u.Po_Unit_Push_Req.push_body);
    service_name = octstr_duplicate(e->u.Po_Unit_Push_Req.service_name);
    push_headers = add_push_flag(e);

    wsp_event = wap_event_create(S_Unit_Push_Req);
    wsp_event->u.S_Unit_Push_Req.addr_tuple =
        wap_addr_tuple_duplicate(e->u.Po_Unit_Push_Req.addr_tuple);
    wsp_event->u.S_Unit_Push_Req.push_id = e->u.Po_Unit_Push_Req.push_id;
    wsp_event->u.S_Unit_Push_Req.push_headers = push_headers;

    wsp_event->u.S_Unit_Push_Req.address_type =
        e->u.Po_Unit_Push_Req.address_type;
    if (smsc_id != NULL)
        wsp_event->u.S_Unit_Push_Req.smsc_id = smsc_id;
    else
        wsp_event->u.S_Unit_Push_Req.smsc_id = NULL;
    if (dlr_url != NULL)
        wsp_event->u.S_Unit_Push_Req.dlr_url = dlr_url;
    else
        wsp_event->u.S_Unit_Push_Req.dlr_url = NULL;
    wsp_event->u.S_Unit_Push_Req.dlr_mask = e->u.Po_Unit_Push_Req.dlr_mask;
    if (smsbox_id != NULL)
        wsp_event->u.S_Unit_Push_Req.smsbox_id = smsbox_id;
    else
        wsp_event->u.S_Unit_Push_Req.smsbox_id = NULL;
    wsp_event->u.S_Unit_Push_Req.service_name = service_name;
    if (push_body != NULL)
        wsp_event->u.S_Unit_Push_Req.push_body = push_body;
    else
        wsp_event->u.S_Unit_Push_Req.push_body = NULL;

    dispatch_to_wsp_unit(wsp_event);
    debug("wap.push.ota", 0, "OTA: made connectionless session service"
          " request");
}
