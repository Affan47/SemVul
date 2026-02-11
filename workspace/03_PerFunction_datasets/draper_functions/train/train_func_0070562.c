clutter_model_get_column_name (ClutterModel *model,
                               guint         column)
{
  ClutterModelClass *klass;

  g_return_val_if_fail (CLUTTER_IS_MODEL (model), NULL);

  if (column >= clutter_model_get_n_columns (model))
    {
      g_warning ("%s: Invalid column id value %d\n", G_STRLOC, column);
      return NULL;
    }

  klass = CLUTTER_MODEL_GET_CLASS (model);
  if (klass->get_column_name)
    return klass->get_column_name (model, column);

  return NULL;
}
