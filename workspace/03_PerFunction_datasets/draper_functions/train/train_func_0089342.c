vmsg_time_sync_reply_stamp(const pmsg_t *mb, const void *unused_q)
{
	struct guid *muid = cast_to_guid_ptr(pmsg_start(mb));
	tm_t now;

	(void) unused_q;
	g_assert(pmsg_is_writable(mb));
	STATIC_ASSERT(sizeof(now) >= 2 * sizeof(uint32));

	tm_now_exact(&now);
	now.tv_sec = clock_loc2gmt(now.tv_sec);

	poke_be32(&muid->v[8], now.tv_sec);
	poke_be32(&muid->v[12], now.tv_usec);

	return TRUE;
}
