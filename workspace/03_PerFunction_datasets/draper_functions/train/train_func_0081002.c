test_context_engine_set_by_global (void)
{
    IBusEngineDesc *engine_desc;
    IBusInputContext *context;

    if (!ibus_bus_get_use_global_engine (bus))
        return;

    context = ibus_bus_create_input_context (bus, "test");
    ibus_input_context_set_capabilities (context, IBUS_CAP_FOCUS);


    ibus_input_context_focus_in (context);

    change_global_engine ();


    ibus_input_context_set_engine (context, BEFORE_ENGINE);

    engine_desc = ibus_input_context_get_engine (context);
    g_assert_cmpstr (ibus_engine_desc_get_name (engine_desc), ==, AFTER_ENGINE);

    g_object_unref (context);
}
