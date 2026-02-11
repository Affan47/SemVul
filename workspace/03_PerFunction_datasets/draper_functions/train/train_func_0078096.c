gog_smoothed_curve_dataset_get_elem (GogDataset const *set, int dim_i)
{
	GogSmoothedCurve const *sc = GOG_SMOOTHED_CURVE (set);
	GogSmoothedCurveClass *klass = (GogSmoothedCurveClass *) G_OBJECT_GET_CLASS (set);
	g_return_val_if_fail (dim_i >= -1 && dim_i <= klass->max_dim, NULL);
	dim_i++;
	return sc->name + dim_i;
}
