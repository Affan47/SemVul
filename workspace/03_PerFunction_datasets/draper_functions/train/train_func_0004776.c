cachefiles_daemon_open(struct inode *inode, struct file *file)
{
	struct cachefiles_cache *cache;

	_enter("");


	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;


	if (xchg(&cachefiles_open, 1) == 1)
		return -EBUSY;


	cache = kzalloc(sizeof(struct cachefiles_cache), GFP_KERNEL);
	if (!cache) {
		cachefiles_open = 0;
		return -ENOMEM;
	}

	mutex_init(&cache->daemon_mutex);
	cache->active_nodes = RB_ROOT;
	rwlock_init(&cache->active_lock);
	init_waitqueue_head(&cache->daemon_pollwq);


	cache->frun_percent = 7;
	cache->fcull_percent = 5;
	cache->fstop_percent = 1;
	cache->brun_percent = 7;
	cache->bcull_percent = 5;
	cache->bstop_percent = 1;

	file->private_data = cache;
	cache->cachefilesd = file;
	return 0;
}
