ShowBestMoveToggled(GtkWidget * pw, tempmapwidget * ptmw)
{

    int f = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pw));

    if (f != ptmw->fShowBestMove) {
        fShowBestMove = ptmw->fShowBestMove = f;
        UpdateTempMapEquities(ptmw);
    }
}
