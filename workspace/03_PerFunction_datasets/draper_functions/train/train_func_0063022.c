on_bt_s_clicked( GtkWidget *widget,
                             gpointer   data )
{
    if (gtk_toggle_button_get_active((GtkToggleButton *)caps_btn) || gtk_toggle_button_get_active((GtkToggleButton *)l_shift_btn) || gtk_toggle_button_get_active((GtkToggleButton *)r_shift_btn))
        display_key_value("S");
    else
        display_key_value("s");
}
