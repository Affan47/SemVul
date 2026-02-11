on_fontpicker_font_set                 (GtkFontButton *fontpicker,
                                        gchar *arg1,
                                        gpointer         user_data)
{
    gpaint_tool *tool = tool_palette_get_tool(GTK_WIDGET(fontpicker), "text");

    const gchar* name = gtk_font_button_get_font_name(fontpicker);
    debug1("font name = %s", name);


    if (tool && tool->attribute)
    {
        (*tool->attribute)(tool, GpaintFont, (gpointer*)name);
    }
}
