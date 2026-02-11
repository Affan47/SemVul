visu_scalar_field_setData(VisuScalarField *field, GArray *data, gboolean xyzOrder)
{
  guint i, j, k, ii;

  g_return_if_fail(field && data);
  g_return_if_fail(data->len == field->priv->nElements[0] *
                   field->priv->nElements[1] * field->priv->nElements[2]);

  DBG_fprintf(stderr, "VisuScalarField: set data from array %p (%d ele.).\n",
              (gpointer)data, data->len);
  field->priv->min = G_MAXFLOAT;
  field->priv->max = -G_MAXFLOAT;
  ii = 0;
  if (xyzOrder)
    for (k = 0 ; k < field->priv->nElements[2] ; k++)
      for (j = 0 ; j < field->priv->nElements[1] ; j++)
	for (i = 0 ; i < field->priv->nElements[0] ; i++)
	  {
	    field->priv->data[i][j][k] = ((double*)data->data)[ii];
	    field->priv->min = MIN(field->priv->data[i][j][k], field->priv->min);
	    field->priv->max = MAX(field->priv->data[i][j][k], field->priv->max);
	    ii += 1;
	  }
  else
    for (i = 0 ; i < field->priv->nElements[0] ; i++)
      for (j = 0 ; j < field->priv->nElements[1] ; j++)
	for (k = 0 ; k < field->priv->nElements[2] ; k++)
	  {
	    field->priv->data[i][j][k] = ((double*)data->data)[ii];
	    field->priv->min = MIN(field->priv->data[i][j][k], field->priv->min);
	    field->priv->max = MAX(field->priv->data[i][j][k], field->priv->max);
	    ii += 1;
	  }
  DBG_fprintf(stderr, " | done.\n");
}
