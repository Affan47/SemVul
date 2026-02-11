sa_remove(struct sa *sa)
{
	LIST_REMOVE(sa, link);
	LOG_DBG((LOG_SA, 70, "sa_remove: SA %p removed from SA list", sa));
	sa_release(sa);
}
