gnc_register_gui_component_internal (const char * component_class)
{
    ComponentInfo *ci;
    gint component_id;

    g_return_val_if_fail (component_class, NULL);


    component_id = next_component_id;


    while (find_component (component_id))
        if (++component_id == NO_COMPONENT)
            component_id++;

    if (component_id < 0)
        PERR("Amazing! Half way to running out of component_ids.");


    ci = g_new0 (ComponentInfo, 1);

    ci->watch_info.event_masks = g_hash_table_new (g_str_hash, g_str_equal);
    ci->watch_info.entity_events = guid_hash_table_new ();

    ci->component_class = g_strdup (component_class);
    ci->component_id = component_id;
    ci->session = NULL;

    components = g_list_prepend (components, ci);


    next_component_id = component_id + 1;

#if CM_DEBUG
    fprintf (stderr, "Register component %d in class %s\n",
             component_id, component_class ? component_class : "(null)");
    dump_components ();
#endif

    return ci;
}
