gtk_multiview_insert_child(GtkMultiview * multiview, GtkWidget * back_child, GtkWidget * child)
{
    GList *list;

    g_return_if_fail(multiview != NULL);
    g_return_if_fail(GTK_IS_MULTIVIEW(multiview));
    g_return_if_fail(child != NULL);
    g_return_if_fail(GTK_IS_WIDGET(child));

    list = g_list_find(multiview->children, back_child);
    if (list == NULL) {
        multiview->children = g_list_prepend(multiview->children, child);
    } else {
        GList *new_el = g_list_alloc();

        new_el->next = list->next;
        new_el->prev = list;
        if (new_el->next)
            new_el->next->prev = new_el;
        new_el->prev->next = new_el;
        new_el->data = (gpointer) child;
    }
    gtk_widget_set_parent(GTK_WIDGET(child), GTK_WIDGET(multiview));

    if (gtk_widget_get_realized(GTK_WIDGET(multiview)))
        gtk_widget_realize(GTK_WIDGET(child));

    if (gtk_widget_get_visible(GTK_WIDGET(multiview)) && gtk_widget_get_visible(GTK_WIDGET(child))) {
        if (gtk_widget_get_mapped(GTK_WIDGET(child)))
            gtk_widget_unmap(GTK_WIDGET(child));
        gtk_widget_queue_resize(GTK_WIDGET(multiview));
    }


    if (multiview->children->next == NULL)
        gtk_multiview_set_current(multiview, child);
}
