gog_dataset_set_dim (GogDataset *set, int dim_i, GOData *val, GError **err)
{
	GogDatasetClass *klass;
	int first, last;

	g_return_if_fail (set != NULL || val == NULL || GO_IS_DATA (val));

	if (set == NULL || !GOG_IS_DATASET (set)) {
		g_warning ("gog_dataset_set_dim called with invalid GogDataset");
		goto done;
	}

	gog_dataset_dims (set, &first, &last);
	if (dim_i < first || dim_i > last) {
		g_warning ("gog_dataset_set_dim called with invalid index (%d)", dim_i);
		goto done;
	}
	klass = GOG_DATASET_GET_CLASS (set);


	if (val != gog_dataset_get_dim (set, dim_i)) {
		gog_dataset_set_dim_internal (set, dim_i, val,
			gog_object_get_graph (GOG_OBJECT (set)));

		if (klass->set_dim)
			(klass->set_dim) (set, dim_i, val, err);
		if (klass->dim_changed)
			(klass->dim_changed) (set, dim_i);
	}

done :

	if (val != NULL)
		g_object_unref (val);
}
