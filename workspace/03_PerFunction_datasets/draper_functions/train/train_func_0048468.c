on_tool_select(gpaint_tool_button* tb)
{

    gpaint_tool_palette *palette = lookup_tool_palette_data(GTK_WIDGET(tb->widget));
    GtkToggleButton *selected = palette->selected;
    if (selected)
    {
        gpaint_tool_button *p =
            (gpaint_tool_button*)gtk_object_get_data(GTK_OBJECT(selected), "tool_button");
        g_assert(p);
        p->handle_click = on_tool_deselect;


        gtk_toggle_button_set_active(palette->selected, FALSE);
    }


    palette->selected = tb->widget;
    tb->handle_click = on_tool_reselect;
    canvas_set_tool(canvas_lookup(GTK_WIDGET(tb->widget)), tb->tool);
}
