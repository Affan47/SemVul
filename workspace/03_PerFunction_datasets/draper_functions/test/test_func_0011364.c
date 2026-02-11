gwy_plain_tool_show_item_changed(GwyContainer *container,
                                 GQuark quark,
                                 GwyPlainTool *plain_tool)
{
    gwy_signal_handler_disconnect(plain_tool->show_field, plain_tool->show_id);
    gwy_object_unref(plain_tool->show_field);

    if (gwy_container_gis_object(container, quark, &plain_tool->show_field)) {
        g_object_ref(plain_tool->show_field);
        plain_tool->show_id
            = g_signal_connect_swapped(plain_tool->show_field, "data-changed",
                                       G_CALLBACK(gwy_plain_tool_show_changed),
                                       plain_tool);
    }

    gwy_plain_tool_show_changed(plain_tool);
}
