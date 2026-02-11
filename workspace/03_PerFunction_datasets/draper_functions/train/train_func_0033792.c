_client_req_get_val(client_req_t *req, const char *key)
{
	int i;

	for (i = 0; i < req->pairs_cnt; i ++) {
		if (! strcmp(key, req->pairs[KEY_INDEX(i)]))
			return req->pairs[VAL_INDEX(i)];
	}
	return NULL;
}
