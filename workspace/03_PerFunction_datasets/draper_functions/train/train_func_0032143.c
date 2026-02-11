uf_combo_box_remove_text(GtkComboBox *combo, int value)
    {
        GList *list = static_cast<GList *>(
                          g_object_get_data(G_OBJECT(combo), "uf-combo-list"));
        if (list != NULL) {
            int i;
            for (i = 0; list != NULL; i++, list = g_list_next(list)) {
                if (value == GPOINTER_TO_INT(list->data)) {
                    gtk_combo_box_remove_text(combo, i);
                    list = g_list_remove(list, list->data);
                    g_object_set_data(G_OBJECT(combo), "uf-combo-list", list);
                    return;
                }
            }
        } else {
            gtk_combo_box_remove_text(combo, value);
        }
    }
