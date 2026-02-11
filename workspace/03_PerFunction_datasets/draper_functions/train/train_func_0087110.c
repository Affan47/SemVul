ggg_close_clicked_cb(GtkButton *button, gpointer user_data)
{
    GncGWENGui *gui = user_data;

    g_return_if_fail(gui);
    g_return_if_fail(gui->state == FINISHED || gui->state == ABORTED);

    ENTER("gui=%p", gui);

    hide_dialog(gui);

    LEAVE(" ");
}
