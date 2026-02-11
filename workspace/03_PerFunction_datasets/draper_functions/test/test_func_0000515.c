_put_group_cache(char *group_name, void *group_uids, int uid_cnt)
{
	struct group_cache_rec *cache_rec;
	int sz;

	pthread_mutex_lock(&group_cache_mutex);
	if (!group_cache_list) {
		group_cache_list = list_create(_cache_del_func);
	}

	sz = sizeof(uid_t) * (uid_cnt);
	cache_rec = xmalloc(sizeof(struct group_cache_rec));
	cache_rec->group_name = xstrdup(group_name);
	cache_rec->uid_cnt    = uid_cnt;
	cache_rec->group_uids = (uid_t *) xmalloc(sizeof(uid_t) + sz);
	if (uid_cnt > 0)
		memcpy(cache_rec->group_uids, group_uids, sz);
	list_append(group_cache_list, cache_rec);
	pthread_mutex_unlock(&group_cache_mutex);
}
