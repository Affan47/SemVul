genmon_constructor(plugin_instance *p)
{
    genmon_priv *gm;

    ENTER;
    gm = (genmon_priv *) p;
    gm->command = "date +%R";
    gm->time = 1;
    gm->textsize = "medium";
    gm->textcolor = "darkblue";
    gm->max_text_len = 30;

    XCG(p->xc, "Command", &gm->command, str);
    XCG(p->xc, "TextSize", &gm->textsize, str);
    XCG(p->xc, "TextColor", &gm->textcolor, str);
    XCG(p->xc, "PollingTime", &gm->time, int);
    XCG(p->xc, "MaxTextLength", &gm->max_text_len, int);

    gm->main = gtk_label_new(NULL);
    gtk_label_set_max_width_chars(GTK_LABEL(gm->main), gm->max_text_len);
    text_update(gm);
    gtk_container_set_border_width (GTK_CONTAINER (p->pwid), 1);
    gtk_container_add(GTK_CONTAINER(p->pwid), gm->main);
    gtk_widget_show_all(p->pwid);
    gm->timer = g_timeout_add((guint) gm->time * 1000,
        (GSourceFunc) text_update, (gpointer) gm);

    RET(1);
}
