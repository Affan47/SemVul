category_ref_cmp ( gpointer src, gpointer dst) {
	GWDBCategory *category = src;


	if (src != NULL && gw_db_category_get_ref ( category) == dst) {
		return 0;
	} else {
		return -1;
	}
}
