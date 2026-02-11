gctt_set_model (GncCombott *combott, GtkTreeModel *model)
{
    GncCombottPrivate *priv;

    g_return_if_fail (GNC_IS_COMBOTT (combott));
    g_return_if_fail (model == NULL || GTK_IS_TREE_MODEL (model));

    priv = GNC_COMBOTT_GET_PRIVATE (combott);

    gctt_rebuild_menu(combott, model);

    priv->model = model;
    g_object_ref (priv->model);
}
