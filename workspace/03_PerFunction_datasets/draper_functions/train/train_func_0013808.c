response_push_connection(WAPEvent *e)
{
    WAPEvent *wsp_event;

    gw_assert(e->type = Pom_Connect_Res);

    wsp_event = wap_event_create(S_Connect_Res);
    wsp_event->u.S_Connect_Res.session_id = e->u.Pom_Connect_Res.session_id;
    wsp_event->u.S_Connect_Res.negotiated_capabilities =
        wsp_cap_duplicate_list(e->u.Pom_Connect_Res.negotiated_capabilities);
    debug("wap.appl", 0, "APPL: making push connect response");

    wsp_session_dispatch_event(wsp_event);
}
