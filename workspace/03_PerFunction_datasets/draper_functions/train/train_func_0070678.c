gwy_plain_tool_selection_item_changed(GwyContainer *container,
                                      GQuark quark,
                                      GwyPlainTool *plain_tool)
{
    gwy_signal_handler_disconnect(plain_tool->selection,
                                  plain_tool->selection_cid);
    gwy_signal_handler_disconnect(plain_tool->selection,
                                  plain_tool->selection_fid);
    gwy_object_unref(plain_tool->selection);

    if (gwy_container_gis_object(container, quark, &plain_tool->selection)) {
        g_object_ref(plain_tool->selection);
        plain_tool->selection_cid
            = g_signal_connect(plain_tool->selection, "changed",
                               G_CALLBACK(gwy_plain_tool_selection_changed),
                               plain_tool);
        plain_tool->selection_fid
            = g_signal_connect(plain_tool->selection, "finished",
                               G_CALLBACK(gwy_plain_tool_selection_finished),
                               plain_tool);
    }

    gwy_plain_tool_selection_changed(plain_tool->selection, -1, plain_tool);
}
