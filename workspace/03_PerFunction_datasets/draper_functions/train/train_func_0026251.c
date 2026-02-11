gwy_tool_stats_copy(GwyToolStats *tool)
{
    GwyPlainTool *plain_tool;
    ToolReportData report_data;
    GtkClipboard *clipboard;
    GdkDisplay *display;
    gssize len;
    gchar *text;

    plain_tool = GWY_PLAIN_TOOL(tool);
    g_return_if_fail(plain_tool->container);
    if (!tool->results_up_to_date)
        gwy_tool_stats_update_labels(tool);

    report_data.results = tool->results;
    report_data.masking = tool->args.masking;
    if (!plain_tool->mask_field)
        report_data.masking = GWY_MASK_IGNORE;
    report_data.same_units = tool->same_units;
    report_data.angle_format = tool->angle_format;
    report_data.container = plain_tool->container;
    report_data.data_field = plain_tool->data_field;
    report_data.id = plain_tool->id;

    text = gwy_tool_stats_create_report(&report_data, &len);
    display = gtk_widget_get_display(GTK_WIDGET(GWY_TOOL(tool)->dialog));
    clipboard = gtk_clipboard_get_for_display(display, GDK_SELECTION_CLIPBOARD);
    gtk_clipboard_set_text(clipboard, text, -1);
    g_free(text);
}
