recruit_curl(struct pool *pool)
{
	struct curl_ent *ce = cgcalloc(sizeof(struct curl_ent), 1);

	ce->curl = curl_easy_init();
	if (unlikely(!ce->curl))
		quit(1, "Failed to init in recruit_curl");

	list_add(&ce->node, &pool->curlring);
	pool->curls++;
}
