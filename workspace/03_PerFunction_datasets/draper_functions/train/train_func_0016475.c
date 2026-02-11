gwy_tool_roughness_selection_changed(GwyPlainTool *plain_tool,
                                     gint hint)
{
    GwyToolRoughness *tool;
    GtkDialog *dialog;
    gint n = 0;

    tool = GWY_TOOL_ROUGHNESS(plain_tool);
    g_return_if_fail(hint <= 0);

    if (plain_tool->selection) {
        n = gwy_selection_get_data(plain_tool->selection, NULL);
        g_return_if_fail(n == 0 || n == 1);
    }

    gwy_tool_roughness_update(tool);
    dialog = GTK_DIALOG(GWY_TOOL(tool)->dialog);
    gtk_dialog_set_response_sensitive(dialog, GTK_RESPONSE_APPLY, n > 0);
    gtk_widget_set_sensitive(tool->save, n > 0);
    gtk_widget_set_sensitive(tool->copy, n > 0);
}
