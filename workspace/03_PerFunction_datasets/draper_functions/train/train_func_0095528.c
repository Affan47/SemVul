input_pad_window_show (void *window_data)
{
    GtkWidget *window;
    InputPadGtkWindow *input_pad_window;

    g_return_if_fail (window_data != NULL &&
                      INPUT_PAD_IS_GTK_WINDOW (window_data));

    window = GTK_WIDGET (window_data);
    input_pad_window = INPUT_PAD_GTK_WINDOW (window);

    if (input_pad_window->priv && !input_pad_window->priv->show_all) {
        gtk_widget_show_all (window);
        input_pad_window->priv->show_all = TRUE;
    } else {
        gtk_widget_show (window);
    }
}
