on_orig_size( GtkToggleButton* btn, MainWin* mw )
{

    if( GTK_IS_MENU_ITEM(btn) )
    {
        gtk_button_clicked( (GtkButton*)mw->btn_orig );
        return;
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(btn)))
        main_win_set_zoom_mode(mw, ZOOM_ORIG);
}
