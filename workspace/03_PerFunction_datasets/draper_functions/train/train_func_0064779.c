gwy_graph_window_key_pressed(GtkWidget *widget,
                             GdkEventKey *event)
{
    enum {
        important_mods = GDK_CONTROL_MASK | GDK_MOD1_MASK | GDK_RELEASE_MASK
    };
    GwyGraphWindow *graph_window;
    gboolean (*method)(GtkWidget*, GdkEventKey*);
    guint state, key;

    gwy_debug("state = %u, keyval = %u", event->state, event->keyval);
    graph_window = GWY_GRAPH_WINDOW(widget);
    state = event->state & important_mods;
    key = event->keyval;


    if (state == GDK_CONTROL_MASK && (key == GDK_C || key == GDK_c)) {
        gwy_graph_window_copy_to_clipboard(graph_window);
        return TRUE;
    }

    method = GTK_WIDGET_CLASS(gwy_graph_window_parent_class)->key_press_event;
    return method ? method(widget, event) : FALSE;
}
