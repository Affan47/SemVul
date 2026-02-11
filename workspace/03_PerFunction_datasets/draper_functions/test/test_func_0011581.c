lcrt_settings_terminal_color_button_clicked(GtkColorButton *widget, gpointer user_data)
{
    struct lcrt_settings *lsettings = (struct lcrt_settings *)user_data;
    struct lcrt_terminal *lterminal;
    GdkColor *color, col;
    typedef void (*vte_set_color_t)(VteTerminal *terminal, const GdkColor *background);
    vte_set_color_t lcrt_terminal_set_color;

    if (lsettings->session) {
        lterminal = lsettings->parent->w_notebook->current_terminal;
        if (lterminal == NULL)
            return;
        gtk_color_button_get_color(widget, &col);
        if (GTK_WIDGET(widget) == lsettings->t_bt_foreground_color)
            vte_terminal_set_color_foreground(lterminal->terminal, &col);
        else
            vte_terminal_set_color_background(lterminal->terminal, &col);
        return;
    }

    if (GTK_WIDGET(widget) == lsettings->t_bt_foreground_color) {
        color = &lsettings->lt_t_fcolor;
        lcrt_terminal_set_color = &vte_terminal_set_color_foreground;
    } else {
        color = &lsettings->lt_t_bcolor;
        lcrt_terminal_set_color = &vte_terminal_set_color_background;
    }

    gtk_color_button_get_color(widget, color);

    list_for_each_entry(lterminal, &lsettings->parent->w_notebook->child, brother) {
        lcrt_terminal_set_color(lterminal->terminal, color);
    }
}
