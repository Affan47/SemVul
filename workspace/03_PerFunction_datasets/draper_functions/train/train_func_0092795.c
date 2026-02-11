gog_smoothed_curve_parent_changed (GogObject *obj, G_GNUC_UNUSED gboolean was_set)
{
	GogSmoothedCurve *sc = GOG_SMOOTHED_CURVE (obj);
	if (sc->name == NULL) {
		GogSmoothedCurveClass *klass = (GogSmoothedCurveClass *) G_OBJECT_GET_CLASS (obj);
		sc->name = g_new0 (GogDatasetElement, klass->max_dim + 2);
	}
	GOG_OBJECT_CLASS (smoothed_curve_parent_klass)->parent_changed (obj, was_set);
}
