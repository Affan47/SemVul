clutter_model_prepend (ClutterModel *model,
                       ...)
{
  ClutterModelIter *iter;
  va_list args;

  g_return_if_fail (CLUTTER_IS_MODEL (model));

  iter = CLUTTER_MODEL_GET_CLASS (model)->insert_row (model, 0);
  g_assert (CLUTTER_IS_MODEL_ITER (iter));

  va_start (args, model);
  clutter_model_iter_set_internal_valist (iter, args);
  va_end (args);

  g_signal_emit (model, model_signals[ROW_ADDED], 0, iter);

  g_object_unref (iter);
}
