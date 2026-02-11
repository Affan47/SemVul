wil6210_debugfs_init_blobs(struct wil6210_priv *wil,
				       struct dentry *dbg)
{
	int i;
	char name[32];

	for (i = 0; i < ARRAY_SIZE(fw_mapping); i++) {
		struct debugfs_blob_wrapper *blob = &wil->blobs[i];
		const struct fw_map *map = &fw_mapping[i];

		if (!map->name)
			continue;

		blob->data = (void * __force)wil->csr + HOSTADDR(map->host);
		blob->size = map->to - map->from;
		snprintf(name, sizeof(name), "blob_%s", map->name);
		wil_debugfs_create_ioblob(name, S_IRUGO, dbg, blob);
	}
}
