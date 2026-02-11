ini_breakpoints_service(Protocol * proto, TCFBroadcastGroup * bcg) {
    int i;
    broadcast_group = bcg;

    {
        static ContextEventListener listener = {
            event_context_changed,
            event_context_changed,
            NULL,
            event_context_started,
            event_context_changed,
            event_context_disposed
        };
        add_context_event_listener(&listener, NULL);
    }
    {
        static MemoryMapEventListener listener = {
            event_context_changed,
            event_code_unmapped,
        };
        add_memory_map_event_listener(&listener, NULL);
    }
    list_init(&breakpoints);
    list_init(&instructions);
    list_init(&evaluations_posted);
    list_init(&evaluations_active);
    for (i = 0; i < ADDR2INSTR_HASH_SIZE; i++) list_init(addr2instr + i);
    for (i = 0; i < ID2BP_HASH_SIZE; i++) list_init(id2bp + i);
    for (i = 0; i < INP2BR_HASH_SIZE; i++) list_init(inp2br + i);
    add_channel_close_listener(channel_close_listener);
    add_command_handler(proto, BREAKPOINTS, "set", command_ini_bps);
    add_command_handler(proto, BREAKPOINTS, "add", command_bp_add);
    add_command_handler(proto, BREAKPOINTS, "change", command_bp_change);
    add_command_handler(proto, BREAKPOINTS, "enable", command_bp_enable);
    add_command_handler(proto, BREAKPOINTS, "disable", command_bp_disable);
    add_command_handler(proto, BREAKPOINTS, "remove", command_bp_remove);
    add_command_handler(proto, BREAKPOINTS, "getIDs", command_get_bp_ids);
    add_command_handler(proto, BREAKPOINTS, "getProperties", command_get_properties);
    add_command_handler(proto, BREAKPOINTS, "getStatus", command_get_status);
    add_command_handler(proto, BREAKPOINTS, "getCapabilities", command_get_capabilities);
    context_extension_offset = context_extension(sizeof(ContextExtensionBP));
#if !defined(_WRS_KERNEL)
    create_eventpoint("main", eventpoint_at_main, NULL);
#endif
}
