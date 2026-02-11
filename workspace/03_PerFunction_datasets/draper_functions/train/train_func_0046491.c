panel_util_get_gfile_root (GFile *file)
{
	GFile *parent;
	GFile *parent_old;


	parent_old = g_object_ref (file);
	parent = g_file_get_parent (file);
	while (parent != NULL) {
		g_object_unref (parent_old);
		parent_old = parent;
		parent = g_file_get_parent (parent);
	}

	return parent_old;
}
