clutter_model_get_last_iter (ClutterModel *model)
{
  ClutterModelIter *retval;
  guint length;

  g_return_val_if_fail (CLUTTER_IS_MODEL (model), NULL);

  length = clutter_model_get_n_rows (model);
  retval = clutter_model_get_iter_at_row (model, length - 1);
  if (retval != NULL)
    g_assert (clutter_model_filter_iter (model, retval) != FALSE);

  return retval;
}
