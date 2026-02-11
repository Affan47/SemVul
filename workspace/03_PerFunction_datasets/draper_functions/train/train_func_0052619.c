gkrellm_fs_add_to_mounts_list(gchar *dir, gchar *dev, gchar *type)
	{
	Mount	*m;

	m = g_new0(Mount, 1);
	m->directory = g_strdup(dir);
	m->device = g_strdup(dev);
	m->type = g_strdup(type);
	mounts_list = g_list_append(mounts_list, m);
	}
