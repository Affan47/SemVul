lcrt_view_on_full_screen_activate(GtkMenuItem *menuitem, gpointer user_data)
{
    struct lcrt_view *lview = (struct lcrt_view *)user_data;

    if (lview->parent->parent->full_screen == FALSE) {
        gtk_window_fullscreen(GTK_WINDOW(lview->parent->parent->window));
        lview->parent->parent->full_screen = TRUE;
    } else {
        gtk_window_unfullscreen(GTK_WINDOW(lview->parent->parent->window));
        lview->parent->parent->full_screen = FALSE;
    }
}
