fill_hour(month_win *mw, gint col, gint row, char *text)
{
    GtkWidget *name, *ev;
#if !(GTK_CHECK_VERSION(2,12,0))
	GtkTooltips *tips = mw->Tooltips;
#endif

    ev = gtk_event_box_new();
    name = gtk_label_new(text);
    gtk_misc_set_alignment(GTK_MISC(name), 0, 0.5);
    CLAWS_SET_TIP(ev, _("Week number"));
    gtk_container_add(GTK_CONTAINER(ev), name);
    gtk_widget_set_size_request(ev, mw->hour_req.width
            , mw->StartDate_button_req.height);
    if (text)
        gtk_table_attach(GTK_TABLE(mw->dtable), ev, col, col+1, row, row+1
             , (GTK_FILL), (0), 0, 0);
    else
        gtk_table_attach(GTK_TABLE(mw->dtable_h), ev, col, col+1, row, row+1
             , (GTK_FILL), (0), 0, 0);
}
