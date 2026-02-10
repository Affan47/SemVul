msgcache_write_tags(MsgInfo *msginfo, FILE *fp)
{
	GSList *cur = msginfo->tags;
	int w_err = 0, wrote = 0;

	WRITE_CACHE_DATA_INT(msginfo->msgnum, fp);
	for (; cur; cur = cur->next) {
		gint id = GPOINTER_TO_INT(cur->data);
		if (tags_get_tag(id) != NULL) {
			WRITE_CACHE_DATA_INT(id, fp);
		}
	}
	WRITE_CACHE_DATA_INT(-1, fp);

	return w_err ? -1 : wrote;
}
