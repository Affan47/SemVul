watch_dir(const char *notify_dir, dev_t file_dev, ino_t file_ino)
{
    struct stat stat;
    dev_t dir_dev;
    ino_t dir_ino;
    DirWatch *dwatch;
    FileWatch *fw;

    if (lstat (notify_dir, &stat) == -1)
	return BAD;

    dwatch = lookup_dirwatch(stat.st_dev, stat.st_ino);
    if (!dwatch) {
	Log::debug ("New DirWatch for %s (%x %x)\n",
		    notify_dir, (int)stat.st_dev, (int)stat.st_ino);
	dwatch = new DirWatch;
	dwatch->hash_link = NULL;
	dwatch->dir_dev = stat.st_dev;
	dwatch->dir_ino = stat.st_ino;
	dwatch->fd = open(notify_dir, O_RDONLY);
	fcntl (dwatch->fd, F_SETSIG, SIGRTMIN);
	fcntl (dwatch->fd, F_NOTIFY,
	       (DN_MODIFY|DN_CREATE|DN_DELETE|DN_RENAME|DN_ATTRIB) | DN_MULTISHOT);
	hash_dirwatch (dwatch);
    }

    fw = lookup_filewatch(file_dev, file_ino);
    if (fw)  {
	if (!fw->has_dir_watch(dwatch)) {
	    fw->add_dir_watch(dwatch);
	    dwatch->file_watches.prepend(fw);
	}
	return OK;
    }


    Log::debug("New FileWatch for %x %x\n", (int)file_dev, (int)file_ino);
    fw = new FileWatch;
    fw->add_dir_watch(dwatch);
    dwatch->file_watches.prepend(fw);
    fw->file_dev = file_dev;
    fw->file_ino = file_ino;
    hash_filewatch(fw);
    return OK;
}
