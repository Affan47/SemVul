gnc_split_reg2_raise (GNCSplitReg2 *gsr)
{
    if (gsr == NULL)
        return;

    if (gsr->window == NULL)
        return;

    gtk_window_present (GTK_WINDOW (gsr->window));
}
