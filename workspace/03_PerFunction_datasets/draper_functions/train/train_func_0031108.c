raw_wrap(const redisReply *r, size_t *sz) {

	char *ret, *p;

	switch(r->type) {
		case REDIS_REPLY_STATUS:
		case REDIS_REPLY_ERROR:
			*sz = 3 + r->len;
			ret = malloc(*sz);
			ret[0] = (r->type == REDIS_REPLY_STATUS?'+':'-');
			memcpy(ret+1, r->str, *sz-3);
			memcpy(ret+*sz - 2, "\r\n", 2);
			return ret;

		case REDIS_REPLY_STRING:
			*sz = 1 + integer_length(r->len) + 2 + r->len + 2;
			p = ret = malloc(*sz);
			p += sprintf(p, "$%d\r\n", r->len);
			memcpy(p, r->str, *sz - 2 - (p-ret));
			memcpy(ret + *sz - 2, "\r\n", 2);
			return ret;

		case REDIS_REPLY_INTEGER:
			*sz = 3 + integer_length(r->integer);
			ret = malloc(4+*sz);
			sprintf(ret, ":%lld\r\n", r->integer);
			return ret;

		case REDIS_REPLY_ARRAY:
			return raw_array(r, sz);

		default:
			*sz = 5;
			ret = malloc(*sz);
			memcpy(ret, "$-1\r\n", 5);
			return ret;
	}
}
