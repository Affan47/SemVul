alloc_raid_set(struct lib_context *lc, const char *who)
{
	struct raid_set *ret;

	if ((ret = dbg_malloc(sizeof(*ret)))) {
		INIT_LIST_HEAD(&ret->list);
		INIT_LIST_HEAD(&ret->sets);
		INIT_LIST_HEAD(&ret->devs);
		ret->status = s_setup;
		ret->type = t_undef;
	} else
		log_alloc_err(lc, who);

	return ret;
}
