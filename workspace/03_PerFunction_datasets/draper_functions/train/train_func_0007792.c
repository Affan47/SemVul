gdl_switcher_map (GtkWidget *widget)
{
    GSList *p;
    GdlSwitcher *switcher = GDL_SWITCHER (widget);

    if (switcher->priv->show) {
        for (p = switcher->priv->buttons; p != NULL; p = p->next) {
            GtkWidget *button = ((Button *) p->data)->button_widget;
            if (gtk_widget_get_visible (button) &&
                !gtk_widget_get_mapped (button))
                gtk_widget_map (button);
        }
    }
    GTK_WIDGET_CLASS (gdl_switcher_parent_class)->map (widget);
}
