allocate_ban(const char *banstr, const char *who, const char *forward)
{
	struct Ban *bptr;
	bptr = rb_bh_alloc(ban_heap);
	bptr->banstr = rb_strdup(banstr);
	bptr->who = rb_strdup(who);
	bptr->forward = forward ? rb_strdup(forward) : NULL;

	return (bptr);
}
