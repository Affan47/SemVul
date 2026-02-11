gdl_switcher_set_show_buttons (GdlSwitcher *switcher, gboolean show)
{
    GSList *p;

    if (switcher->priv->show == show)
        return;

    for (p = switcher->priv->buttons; p != NULL; p = p->next) {
        Button *button = p->data;

        if (show && gtk_widget_get_visible (button->page))
            gtk_widget_show (button->button_widget);
        else
            gtk_widget_hide (button->button_widget);
    }
    gdl_switcher_update_lone_button_visibility (switcher);
    switcher->priv->show = show;

    gtk_widget_queue_resize (GTK_WIDGET (switcher));
}
