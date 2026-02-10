create_font_btn (const PreferencesWidget * widget, GtkWidget * * label,
 GtkWidget * * font_btn, const char * domain)
{
    *font_btn = gtk_font_button_new();
    gtk_font_button_set_use_font(GTK_FONT_BUTTON(*font_btn), TRUE);
    gtk_font_button_set_use_size(GTK_FONT_BUTTON(*font_btn), TRUE);
    gtk_widget_set_hexpand(*font_btn, TRUE);
    if (widget->label) {
        * label = gtk_label_new_with_mnemonic (dgettext (domain, widget->label));
        gtk_label_set_use_markup(GTK_LABEL(*label), TRUE);
        gtk_misc_set_alignment(GTK_MISC(*label), 1, 0.5);
        gtk_label_set_justify(GTK_LABEL(*label), GTK_JUSTIFY_RIGHT);
        gtk_label_set_mnemonic_widget(GTK_LABEL(*label), *font_btn);
    }

    if (widget->data.font_btn.title)
        gtk_font_button_set_title (GTK_FONT_BUTTON (* font_btn),
         dgettext (domain, widget->data.font_btn.title));

    char * name = widget_get_string (widget);
    if (name)
    {
        gtk_font_button_set_font_name ((GtkFontButton *) * font_btn, name);
        g_free (name);
    }

    g_signal_connect (* font_btn, "font_set", (GCallback) on_font_btn_font_set, (void *) widget);
}
