combo_realized(GtkWidget *parent,
               GtkWidget *combo)
{
    GtkTreeModel* (*model_creator)(GtkWidget *widget);
    GtkTreeModel *model;
    gint value;

    model_creator = g_object_get_data(G_OBJECT(combo), "model-creator");
    g_return_if_fail(model_creator);
    model = model_creator(parent);
    g_return_if_fail(GTK_IS_TREE_MODEL(model));

    gtk_combo_box_set_model(GTK_COMBO_BOX(combo), model);
    value = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(combo),
                                              "initial-value"));
    combo_set_current(combo, value);
}
