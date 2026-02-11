image_get_version(void)
{
	struct image_cfg_element *e;

	e = image_find_option(IMAGE_CFG_VERSION);
	if (!e)
		return -1;

	return e->version;
}
