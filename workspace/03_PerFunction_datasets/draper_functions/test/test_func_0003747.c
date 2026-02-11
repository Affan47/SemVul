musicindex_opendir(request_rec *r, mu_dir *dir, mu_pack *const pack,
			const mu_ent_names * const names, unsigned long soptions)
{
	const mu_config *const conf = (mu_config *)ap_get_module_config(r->per_dir_config, &musicindex_module);


	dir->dir = NULL;


	if (conf->cache && conf->cache->opendir)
		dir->dir = conf->cache->opendir(r, pack, names->filename, names->uri, soptions);


	if (dir->dir == NULL) {
		dir->dir = opendir(names->filename);
		dir->handled = 0;
	}
	else {
		dir->handled = 1;
	}
}
