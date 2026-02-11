digit_hbox_get_code_point (GtkWidget *digit_hbox)
{
    GList *list;
    GtkComboBox *combobox;
    GtkTreeModel *model;
    GtkTreeIter iter;
    GString *string = NULL;
    gchar *line = NULL;
    guint base = 0;
    guint code;

    list = gtk_container_get_children (GTK_CONTAINER (digit_hbox));
    string = g_string_new (NULL);

    while (list) {
        g_return_val_if_fail (GTK_IS_COMBO_BOX (list->data), 0);
        combobox = GTK_COMBO_BOX (list->data);

        if (!gtk_widget_get_visible (GTK_WIDGET (combobox))) {
            break;
        }
        base = input_pad_gtk_combo_box_get_base (INPUT_PAD_GTK_COMBO_BOX (combobox));
        model = gtk_combo_box_get_model (combobox);
        if (!gtk_combo_box_get_active_iter (combobox, &iter)) {
            g_warning ("Could not find active iter");
            line = g_strdup ("0");
        } else {
            gtk_tree_model_get (model, &iter, DIGIT_TEXT_COL, &line, -1);
        }
        g_string_append (string, line);
        g_free (line);
        list = list->next;
    }
    line = g_string_free (string, FALSE);
    g_return_val_if_fail (line != NULL && base > 0, 0);

    code = (guint) g_ascii_strtoll (line, NULL, base);
    g_free (line);
    return code;
}
