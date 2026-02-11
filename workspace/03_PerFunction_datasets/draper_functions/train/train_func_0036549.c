bus_input_context_set_engine (BusInputContext *context,
                              BusEngineProxy  *engine)
{
    g_assert (BUS_IS_INPUT_CONTEXT (context));

    if (context->engine == engine)
        return;

    if (context->engine != NULL) {
        bus_input_context_unset_engine (context);
    }

    if (engine == NULL) {
        bus_input_context_disable (context);
    }
    else {
        gint i;
        context->engine = engine;
        g_object_ref (context->engine);


        for (i = 0; i < G_N_ELEMENTS(engine_signals); i++) {
            g_signal_connect (context->engine,
                              engine_signals[i].name,
                              engine_signals[i].callback,
                              context);
        }
        if (context->has_focus) {
            bus_engine_proxy_focus_in (context->engine);
            bus_engine_proxy_enable (context->engine);
            bus_engine_proxy_set_capabilities (context->engine, context->capabilities);
            bus_engine_proxy_set_cursor_location (context->engine, context->x, context->y, context->w, context->h);
            bus_engine_proxy_set_content_type (context->engine, context->purpose, context->hints);
        }
    }
    g_signal_emit (context,
                   context_signals[ENGINE_CHANGED],
                   0);
}
