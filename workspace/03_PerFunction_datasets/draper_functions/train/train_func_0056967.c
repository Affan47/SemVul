visu_scalar_field_setBox(VisuBoxed *self, VisuBox *box, gboolean update _U_)
{
  VisuScalarField *field;

  g_return_val_if_fail(VISU_IS_SCALAR_FIELD_TYPE(self), FALSE);
  field = VISU_SCALAR_FIELD(self);

  DBG_fprintf(stderr, "VisuScalarField: set the bounding box to %p.\n", (gpointer)box);
  if (field->priv->box == box)
    return FALSE;

  if (field->priv->box)
    g_object_unref(field->priv->box);
  if (box)
    g_object_ref(box);
  field->priv->box = box;

  return TRUE;
}
