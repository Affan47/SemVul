fill_hour(day_win *dw, gint col, gint row, char *text)
{
    GtkWidget *name, *ev;

    ev = gtk_event_box_new();
    name = gtk_label_new(text);
    gtk_container_add(GTK_CONTAINER(ev), name);
    if ((row % 2) == 1)
        gtk_widget_modify_bg(ev, GTK_STATE_NORMAL, &dw->bg1);
    else
        gtk_widget_modify_bg(ev, GTK_STATE_NORMAL, &dw->bg2);
    gtk_widget_set_size_request(ev, dw->hour_req.width
            , dw->StartDate_button_req.height);
    if (text)
        gtk_table_attach(GTK_TABLE(dw->dtable), ev, col, col+1, row, row+1
             , (GTK_FILL), (0), 0, 0);
    else
        gtk_table_attach(GTK_TABLE(dw->dtable_h), ev, col, col+1, row, row+1
             , (GTK_FILL), (0), 0, 0);
}
