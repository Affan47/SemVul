svg_init()
{
	if (NULL != clade_css_map_file) {
		css_map = read_css_map();
		if (NULL == css_map)
			return FAILURE;
	}
	if (NULL != ornament_map_file) {
		ornament_map = read_ornament_map();
		if (NULL == ornament_map)
			return FAILURE;
	}
	if (NULL != url_map_file) {
		url_map = read_url_map();
		if (NULL == url_map)
			return FAILURE;
	}
	init_done = 1;

	return SUCCESS;
}
