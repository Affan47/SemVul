visu_scalar_field_getMinMax(VisuScalarField *field, double minmax[2])
{
  g_return_if_fail(field);

  minmax[0] = field->priv->min;
  minmax[1] = field->priv->max;
}
