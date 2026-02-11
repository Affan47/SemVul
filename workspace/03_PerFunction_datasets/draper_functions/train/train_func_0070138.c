fp_print_data_delete(struct fp_dev *dev,
	enum fp_finger finger)
{
	int r;
	gchar *path = get_path_to_print(dev, finger);

	fp_dbg("remove finger %d at %s", finger, path);
	r = g_unlink(path);
	g_free(path);
	if (r < 0)
		fp_dbg("unlink failed with error %d", r);


	return r;
}
