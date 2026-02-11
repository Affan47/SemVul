vev_bh_cmp(void *priv, void *a, void *b)
{
	struct vev_base *evb;
	struct vev *ea, *eb;

	CAST_OBJ_NOTNULL(evb, priv, VEV_BASE_MAGIC);
	CAST_OBJ_NOTNULL(ea, a, VEV_MAGIC);
	CAST_OBJ_NOTNULL(eb, b, VEV_MAGIC);
	return (ea->__when < eb->__when);
}
