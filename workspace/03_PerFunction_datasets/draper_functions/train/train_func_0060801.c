combo_box_changed (GtkComboBox *combo_box, struct _crit_data *data)
{
    GNCSearchParam *param;
    GNCSearchCoreType *newelem;
    GtkTreeModel *model;
    GtkTreeIter iter;

    if (!gtk_combo_box_get_active_iter(combo_box, &iter))
        return;
    model = gtk_combo_box_get_model(combo_box);
    gtk_tree_model_get(model, &iter, SEARCH_COL_POINTER, &param, -1);

    if (gnc_search_param_type_match (param, data->param))
    {

        data->param = param;
        return;
    }
    data->param = param;


    if (data->elemwidget)
        gtk_container_remove (GTK_CONTAINER (data->container), data->elemwidget);
    g_object_unref (G_OBJECT (data->element));

    newelem = gnc_search_core_type_new_type_name
              (gnc_search_param_get_param_type (param));
    data->element = newelem;
    data->elemwidget = gnc_search_core_type_get_widget (newelem);
    if (data->elemwidget)
    {
        gtk_box_pack_start (GTK_BOX (data->container), data->elemwidget,
                            FALSE, FALSE, 0);
    }


    gtk_widget_show_all (data->container);


    gtk_widget_queue_resize (GTK_WIDGET (data->dialog));


    gnc_search_core_type_grab_focus (newelem);
    gnc_search_core_type_editable_enters (newelem);
}
