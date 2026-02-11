gnc_ui_source_menu_create(QuoteSourceType type)
{
    gint i, max;
    const gchar *name;
    gboolean supported;
    GtkListStore *store;
    GtkTreeIter iter;
    GtkWidget *combo;
    GtkCellRenderer *renderer;
    gnc_quote_source *source;

    store = gtk_list_store_new(NUM_SOURCE_COLS, G_TYPE_STRING, G_TYPE_BOOLEAN);
    if (type == SOURCE_CURRENCY)
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           SOURCE_COL_NAME, _("Currency"),
                           SOURCE_COL_FQ_SUPPORTED, TRUE,
                           -1);
    }
    else
    {
        max = gnc_quote_source_num_entries(type);
        for (i = 0; i < max; i++)
        {
            source = gnc_quote_source_lookup_by_ti(type, i);
            if (source == NULL)
                break;
            name = gnc_quote_source_get_user_name(source);
            supported = gnc_quote_source_get_supported(source);
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               SOURCE_COL_NAME, name,
                               SOURCE_COL_FQ_SUPPORTED, supported,
                               -1);
        }
    }

    combo = gtk_combo_box_new_with_model(GTK_TREE_MODEL(store));
    g_object_unref(store);
    renderer = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo), renderer, TRUE);
    gtk_cell_layout_add_attribute(GTK_CELL_LAYOUT(combo), renderer,
                                  "text", SOURCE_COL_NAME);
    gtk_cell_layout_add_attribute(GTK_CELL_LAYOUT(combo), renderer,
                                  "sensitive", SOURCE_COL_FQ_SUPPORTED);
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
    gtk_widget_show(combo);
    return combo;
}
