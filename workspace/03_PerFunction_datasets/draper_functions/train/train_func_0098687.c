gda_data_model_iter_get_holder_for_field (GdaDataModelIter *iter, gint col)
{
	g_return_val_if_fail (GDA_IS_DATA_MODEL_ITER (iter), NULL);
	g_return_val_if_fail (iter->priv, NULL);

	return gda_set_get_nth_holder ((GdaSet *) iter, col);
}
