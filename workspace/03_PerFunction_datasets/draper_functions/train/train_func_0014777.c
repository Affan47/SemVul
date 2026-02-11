infowin_label_set_text (GtkWidget * widget, char * text)
{
    char * tmp;

    if (text)
    {
        tmp = g_strdup_printf("<span size=\"small\">%s</span>", text);
        gtk_label_set_text ((GtkLabel *) widget, tmp);
        g_free (tmp);
        str_unref (text);
    }
    else
        gtk_label_set_text ((GtkLabel *) widget,
         _("<span size=\"small\">n/a</span>"));

    gtk_label_set_use_markup ((GtkLabel *) widget, TRUE);
}
