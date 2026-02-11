window_menu_on_draw (GtkWidget *widget,
                     cairo_t   *cr,
                     gpointer   data)
{
        GtkStyleContext *context;
        GtkStateFlags    state;
        WindowMenu      *window_menu = data;

	if (!gtk_widget_has_focus (window_menu->applet))
                return FALSE;

        state = gtk_widget_get_state_flags (widget);
        context = gtk_widget_get_style_context (widget);
        gtk_style_context_save (context);
        gtk_style_context_set_state (context, state);

        cairo_save (cr);
        gtk_render_focus (context, cr,
                          0., 0.,
                          gtk_widget_get_allocated_width (widget),
                          gtk_widget_get_allocated_height (widget));
        cairo_restore (cr);

        gtk_style_context_restore (context);

	return FALSE;
}
