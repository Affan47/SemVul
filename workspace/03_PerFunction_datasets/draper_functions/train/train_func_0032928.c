rinoo_inotify_add_watch(t_inotify *inotify, const char *path, t_inotify_type type, bool recursive)
{
	int wd;
	int nb;
	t_fs_entry *entry;
	t_inotify_watch *watch;

	if (inotify->nb_watches >= ARRAY_SIZE(inotify->watches)) {
		return NULL;
	}
	wd = inotify_add_watch(inotify->node.fd, path, type);
	if (wd < 0) {
		return NULL;
	}
	if ((unsigned int) wd >= ARRAY_SIZE(inotify->watches)) {
		inotify_rm_watch(inotify->node.fd, wd);
		return NULL;
	}
	watch = calloc(1, sizeof(*watch));
	if (watch == NULL) {
		inotify_rm_watch(inotify->node.fd, wd);
		return NULL;
	}
	watch->wd = wd;
	watch->path = strdup(path);
	if (watch->path == NULL) {
		inotify_rm_watch(inotify->node.fd, wd);
		free(watch);
		return NULL;
	}
	if (recursive) {
		nb = 0;
		entry = NULL;
		while (rinoo_fs_browse(path, &entry) == 0 && entry != NULL) {
			nb++;
			if (nb > 100) {
				nb = 0;
				rinoo_task_pause(inotify->node.sched);
			}
			if (S_ISDIR(entry->stat.st_mode)) {
				rinoo_inotify_add_watch(inotify, buffer_ptr(entry->path), type, false);
			}
		}
	}
	inotify->watches[wd] = watch;
	inotify->nb_watches++;
	return watch;
}
