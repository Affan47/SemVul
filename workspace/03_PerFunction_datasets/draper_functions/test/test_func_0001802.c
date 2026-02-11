input_pad_gtk_window_real_destroy (GtkWidget *widget)
#else
input_pad_gtk_window_real_destroy (GtkObject *widget)
#endif
{
    InputPadGtkWindow *window = INPUT_PAD_GTK_WINDOW (widget);

    if (window->priv) {
        if (window->priv->group) {
            input_pad_group_destroy (window->priv->group);
            window->priv->group = NULL;
        }
        if (window->priv->color_gray) {
            gdk_color_free (window->priv->color_gray);
            window->priv->color_gray = NULL;
        }
#ifdef MODULE_XTEST_GDK_BASE
        if (use_module_xtest) {
            input_pad_gtk_window_xtest_gdk_destroy (window);
        }
#endif
        if (window->priv->kbdui) {
            input_pad_gtk_window_kbdui_destroy (window);
        }
        g_free (window->priv->kbdui_name);
        window->priv->kbdui_name = NULL;
        window->priv = NULL;
    }
#if GTK_CHECK_VERSION (2, 90, 0)
    GTK_WIDGET_CLASS (input_pad_gtk_window_parent_class)->destroy (widget);
#else
    GTK_OBJECT_CLASS (input_pad_gtk_window_parent_class)->destroy (widget);
#endif
}
