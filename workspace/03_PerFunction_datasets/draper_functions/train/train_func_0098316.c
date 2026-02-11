smsg_alloc(gnet_search_t sh, pmsg_t *mb, query_hashvec_t *qhv)
{
	smsg_t *sb;

	WALLOC(sb);
	sb->shandle = sh;
	sb->mb = mb;
	sb->qhv = qhv;

	return sb;
}
