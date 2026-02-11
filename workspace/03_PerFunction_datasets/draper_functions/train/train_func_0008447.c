xl_axis_swap_elem (GogAxis *a, GogAxis *b, unsigned dim)
{
	GOData *a_dat = gog_dataset_get_dim (GOG_DATASET (a), dim);
	GOData *b_dat = gog_dataset_get_dim (GOG_DATASET (b), dim);

	if (a_dat != NULL) g_object_ref (a_dat);
	if (b_dat != NULL) g_object_ref (b_dat);
	gog_dataset_set_dim (GOG_DATASET (a), dim, b_dat, NULL);
	gog_dataset_set_dim (GOG_DATASET (b), dim, a_dat, NULL);
}
