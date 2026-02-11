gog_axis_dataset_get_elem (GogDataset const *set, int dim_i)
{
	GogAxis *axis = GOG_AXIS (set);
	if (GOG_AXIS_ELEM_MIN <= dim_i && dim_i < GOG_AXIS_ELEM_CROSS_POINT)
		return &axis->source[dim_i];
	if (dim_i == GOG_AXIS_ELEM_CROSS_POINT) {
		return &(axis->base.cross_location);
	}
	return NULL;
}
