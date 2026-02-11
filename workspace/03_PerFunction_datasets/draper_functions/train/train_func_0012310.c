deskno_constructor(plugin_instance *p)
{
    deskno_priv *dc;

    ENTER;
    dc = (deskno_priv *) p;
    dc->main = gtk_button_new();
    gtk_button_set_relief(GTK_BUTTON(dc->main), GTK_RELIEF_NONE);
    g_signal_connect(G_OBJECT(dc->main), "clicked", G_CALLBACK(clicked),
        (gpointer) dc);
    g_signal_connect(G_OBJECT(dc->main), "scroll-event", G_CALLBACK(scrolled),
        (gpointer) dc);
    dc->namew = gtk_label_new("ww");
    gtk_container_add(GTK_CONTAINER(dc->main), dc->namew);
    gtk_container_add(GTK_CONTAINER(p->pwid), dc->main);


    gtk_widget_show_all(p->pwid);
    name_update(dc->main, dc);
    update(dc->main, dc);
    g_signal_connect(G_OBJECT(fbev), "current_desktop", G_CALLBACK
        (name_update), (gpointer) dc);
    g_signal_connect(G_OBJECT(fbev), "number_of_desktops", G_CALLBACK
        (update), (gpointer) dc);
    RET(1);
}
