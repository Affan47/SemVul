options_repeat_mode_changed_cb (GtkToggleButton *button, gpointer user_data) {

    GUI *appGUI = (GUI *)user_data;

    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(appGUI->opt->rna_radio_button)) == TRUE) {
       config.repeat_mode = REPEAT_NONE;
    } else if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(appGUI->opt->rwa_radio_button)) == TRUE) {
       config.repeat_mode = REPEAT_WRONG;
    } else {
       config.repeat_mode = REPEAT_ALL;
    }
}
