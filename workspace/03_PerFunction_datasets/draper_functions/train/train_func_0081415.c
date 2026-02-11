cb_update_setting (GtkWidget *widget, GdkEvent *event, gpointer data)
{
    int nVal[] =
    {
        gtk_spin_button_get_value (GTK_SPIN_BUTTON (g_pSpinButtonCandPerPage)),
        gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (g_pCheckButtonSpaceAsSelection)),
        gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (g_pCheckButtonEscCleanAllBuf)),
        gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (g_pCheckButtonAutoShiftCur)),
        gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (g_pCheckButtonAddPhraseForward))
    };

    if (!chewing_config_save (nVal))
    {
        chewing_config_close ();
        return FALSE;
    }

    chewing_config_close ();

    gtk_widget_destroy (hime_chewing_window);
    hime_chewing_window = NULL;
    return TRUE;
}
