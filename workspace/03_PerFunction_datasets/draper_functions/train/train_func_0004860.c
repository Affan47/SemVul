lcrt_edit_on_copy_activate(GtkMenuItem *menuitem, gpointer user_data)
{
    struct lcrt_window *lwindow = (struct lcrt_window *)user_data;
    struct lcrt_terminal *lterminal = lwindow->w_notebook->current_terminal;

    debug_where();
    if (lcrt_terminal_has_selection(lwindow) == FALSE)
        return;
    debug_where();
    vte_terminal_copy_clipboard(lterminal->terminal);
}
