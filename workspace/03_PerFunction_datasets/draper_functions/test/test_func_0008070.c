evl_new (GelETree *cond, GelETree *body, gboolean is_while, gboolean body_first)
{
	GelEvalLoop *evl;
#ifdef MEM_DEBUG_FRIENDLY
	evl = g_new0 (GelEvalLoop, 1);
#else
	if G_UNLIKELY (free_evl == NULL)
		_gel_make_free_evl ();
	evl = free_evl;
	free_evl = (GelEvalLoop *)free_evl->condition;
#endif
	evl->condition = cond;
	evl->body = body;
	evl->is_while = is_while ? 1 : 0;
	evl->body_first = body_first ? 1 : 0;
	return evl;
}
