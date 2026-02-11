b43legacy_debugfs_add_device(struct b43legacy_wldev *dev)
{
	struct b43legacy_dfsentry *e;
	struct b43legacy_txstatus_log *log;
	char devdir[16];

	B43legacy_WARN_ON(!dev);
	e = kzalloc(sizeof(*e), GFP_KERNEL);
	if (!e) {
		b43legacyerr(dev->wl, "debugfs: add device OOM\n");
		return;
	}
	e->dev = dev;
	log = &e->txstatlog;
	log->log = kcalloc(B43legacy_NR_LOGGED_TXSTATUS,
			   sizeof(struct b43legacy_txstatus), GFP_KERNEL);
	if (!log->log) {
		b43legacyerr(dev->wl, "debugfs: add device txstatus OOM\n");
		kfree(e);
		return;
	}
	log->end = -1;
	spin_lock_init(&log->lock);

	dev->dfsentry = e;

	snprintf(devdir, sizeof(devdir), "%s", wiphy_name(dev->wl->hw->wiphy));
	e->subdir = debugfs_create_dir(devdir, rootdir);
	if (!e->subdir || IS_ERR(e->subdir)) {
		if (e->subdir == ERR_PTR(-ENODEV)) {
			b43legacydbg(dev->wl, "DebugFS (CONFIG_DEBUG_FS) not "
			       "enabled in kernel config\n");
		} else {
			b43legacyerr(dev->wl, "debugfs: cannot create %s directory\n",
			       devdir);
		}
		dev->dfsentry = NULL;
		kfree(log->log);
		kfree(e);
		return;
	}

#define ADD_FILE(name, mode)	\
	do {							\
		struct dentry *d;				\
		d = debugfs_create_file(__stringify(name),	\
					mode, e->subdir, dev,	\
					&fops_##name.fops);	\
		e->file_##name.dentry = NULL;			\
		if (!IS_ERR(d))					\
			e->file_##name.dentry = d;		\
	} while (0)


	ADD_FILE(tsf, 0600);
	ADD_FILE(ucode_regs, 0400);
	ADD_FILE(shm, 0400);
	ADD_FILE(txstat, 0400);
	ADD_FILE(restart, 0200);

#undef ADD_FILE

	b43legacy_add_dynamic_debug(dev);
}
