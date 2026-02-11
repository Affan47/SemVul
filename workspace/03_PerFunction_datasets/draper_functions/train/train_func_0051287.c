sixtp_parse_push (sixtp *sixtp,
                  sixtp_push_handler push_handler,
                  gpointer push_user_data,
                  gpointer data_for_top_level,
                  gpointer global_data,
                  gpointer *parse_result)
{
    sixtp_parser_context *ctxt;
    xmlParserCtxtPtr xml_context;

    if (!push_handler)
    {
        g_critical("No push handler specified");
        return FALSE;
    }

    if (!(ctxt = sixtp_context_new(sixtp, global_data, data_for_top_level)))
    {
        g_critical("sixtp_context_new returned null");
        return FALSE;
    }

    xml_context = xmlCreatePushParserCtxt(&ctxt->handler, &ctxt->data,
                                          NULL, 0, NULL);
    ctxt->data.saxParserCtxt = xml_context;
    ctxt->data.bad_xml_parser = sixtp_dom_parser_new(gnc_bad_xml_end_handler,
                                NULL, NULL);

    (*push_handler)(xml_context, push_user_data);

    sixtp_context_run_end_handler(ctxt);

    if (ctxt->data.parsing_ok)
    {
        if (parse_result)
            *parse_result = ctxt->top_frame->frame_data;
        sixtp_context_destroy(ctxt);
        return TRUE;
    }
    else
    {
        if (parse_result)
            *parse_result = NULL;
        if (g_slist_length(ctxt->data.stack) > 1)
            sixtp_handle_catastrophe(&ctxt->data);
        sixtp_context_destroy(ctxt);
        return FALSE;
    }
}
