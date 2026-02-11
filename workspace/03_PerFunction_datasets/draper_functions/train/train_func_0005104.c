on_filter_entry_key_press_event(GtkWidget* widget, GdkEventKey* event, gpointer user_data)
{
    QuickOpenDialog* self = user_data;

    if (!(event->state & (GDK_SHIFT_MASK | GDK_CONTROL_MASK)))
    {
        switch (event->keyval)
        {
            case GDK_KEY_Up:
                quick_open_dialog_move_selection(self, MOVE_SELECTION_DIFF, -1);
                return TRUE;
            case GDK_KEY_Down:
                quick_open_dialog_move_selection(self, MOVE_SELECTION_DIFF, 1);
                return TRUE;
            case GDK_KEY_Page_Up:
                quick_open_dialog_move_selection(self, MOVE_SELECTION_DIFF, -5);
                return TRUE;
            case GDK_KEY_Page_Down:
                quick_open_dialog_move_selection(self, MOVE_SELECTION_DIFF, 5);
                return TRUE;
            case GDK_KEY_Home:
                quick_open_dialog_move_selection(self, MOVE_SELECTION_FIRST, 0);
                return TRUE;
            case GDK_KEY_End:
                quick_open_dialog_move_selection(self, MOVE_SELECTION_END, 0);
                return TRUE;

            case GDK_KEY_Return:
            case GDK_KEY_KP_Enter:
                gtk_dialog_response(GTK_DIALOG(self), GTK_RESPONSE_ACCEPT);
                return TRUE;
        }
    }

    return FALSE;
}
