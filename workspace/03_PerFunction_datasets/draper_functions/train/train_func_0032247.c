bson_hgetall_reply(const redisReply *r) {

	bson_t *broot;
	unsigned int i;

	if(r->elements % 2 != 0) {
		return NULL;
	}

	broot = bson_object();
	for(i = 0; i < r->elements; i += 2) {
		redisReply *k = r->element[i], *v = r->element[i+1];


		if(k->type != REDIS_REPLY_STRING || v->type != REDIS_REPLY_STRING) {
			bson_free(broot);
			return NULL;
		}
		bson_object_set_new(broot, k->str, k->len, bson_string(v->str, v->len));
	}
	return broot;
}
