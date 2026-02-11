plot_annotations_set_hd_catalog(plotann_t* ann, const char* hdfn) {
	if (ann->hd_catalog)
		free(ann->hd_catalog);
	ann->hd_catalog = strdup(hdfn);
	return 0;
}
