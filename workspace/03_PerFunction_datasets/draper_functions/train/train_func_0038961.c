gda_data_model_iter_is_valid (GdaDataModelIter *iter)
{
	g_return_val_if_fail (GDA_IS_DATA_MODEL_ITER (iter), FALSE);
	g_return_val_if_fail (iter->priv, FALSE);

	return iter->priv->row >= 0 ? TRUE : FALSE;
}
