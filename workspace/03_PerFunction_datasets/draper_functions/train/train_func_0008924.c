input_pad_gtk_window_real_realize (GtkWidget *window)
{
#ifdef MODULE_XTEST_GDK_BASE
    InputPadGtkWindow *input_pad = INPUT_PAD_GTK_WINDOW (window);

    if (use_module_xtest) {
        input_pad_gtk_window_xtest_gdk_setup (input_pad);
    }
#endif
    GTK_WIDGET_CLASS (input_pad_gtk_window_parent_class)->realize (window);
}
