bus_input_context_enable (BusInputContext *context)
{
    g_assert (BUS_IS_INPUT_CONTEXT (context));

    if (!context->has_focus) {
        return;
    }

    if (context->engine == NULL) {
        IBusEngineDesc *desc = NULL;
        g_signal_emit (context,
                       context_signals[REQUEST_ENGINE], 0,
                       NULL,
                       &desc);
        if (desc != NULL) {
            bus_input_context_set_engine_by_desc (context,
                            desc,
                            g_gdbus_timeout,
                            NULL,
                            NULL,
                            NULL);
        }
    }

    if (context->engine == NULL)
        return;

    bus_engine_proxy_focus_in (context->engine);
    bus_engine_proxy_enable (context->engine);
    bus_engine_proxy_set_capabilities (context->engine, context->capabilities);
    bus_engine_proxy_set_cursor_location (context->engine, context->x, context->y, context->w, context->h);
    bus_engine_proxy_set_content_type (context->engine, context->purpose, context->hints);
}
