gnc_item_list_key_event (GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    GncItemList *item_list = GNC_ITEM_LIST (data);
    GtkTreeSelection *selection = NULL;
    GtkTreeIter iter;
    GtkTreeModel *model;
    gchar *string;

    switch (event->keyval)
    {
    case GDK_KEY_Return:
        selection = gtk_tree_view_get_selection (item_list->tree_view);
        if (!gtk_tree_selection_get_selected (selection, &model, &iter))
            return FALSE;

        gtk_tree_model_get (model, &iter, 0, &string, -1);

        g_signal_emit (G_OBJECT (item_list),
                       gnc_item_list_signals[ACTIVATE_ITEM],
                       0,
                       string);
        g_free(string);
        return TRUE;

    case GDK_KEY_Page_Up:
    case GDK_KEY_Page_Down:
    case GDK_KEY_Up:
    case GDK_KEY_Down:

        return FALSE;
    }


    g_signal_stop_emission_by_name (G_OBJECT (widget), "key_press_event");

    g_signal_emit (G_OBJECT (item_list),
                   gnc_item_list_signals[KEY_PRESS_EVENT], 0, event);

    return TRUE;
}
