clutter_model_prependv (ClutterModel *model,
                        guint         n_columns,
                        guint        *columns,
                        GValue       *values)
{
  ClutterModelPrivate *priv;
  ClutterModelIter *iter;
  gint i;
  gboolean resort = FALSE;

  g_return_if_fail (CLUTTER_IS_MODEL (model));
  g_return_if_fail (n_columns <= clutter_model_get_n_columns (model));
  g_return_if_fail (columns != NULL);
  g_return_if_fail (values != NULL);

  priv = model->priv;

  iter = CLUTTER_MODEL_GET_CLASS (model)->insert_row (model, 0);
  g_assert (CLUTTER_IS_MODEL_ITER (iter));

  for (i = 0; i < n_columns; i++)
    {
      if (priv->sort_column == columns[i])
        resort = TRUE;

      clutter_model_iter_set_value (iter, columns[i], &values[i]);
    }

  g_signal_emit (model, model_signals[ROW_ADDED], 0, iter);

  if (resort)
    clutter_model_resort (model);

  g_object_unref (iter);
}
