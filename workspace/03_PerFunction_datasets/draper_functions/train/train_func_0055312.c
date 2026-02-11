raw_ws_extract(struct http_client *c, const char *p, size_t sz) {

	struct cmd *cmd = NULL;
	void *reader = NULL;
	redisReply *reply = NULL;
	void **reply_ptr = (void**)&reply;
	unsigned int i;
	(void)c;


	reader = redisReaderCreate();


	redisReaderFeed(reader, (char*)p, sz);


	if(redisReaderGetReply(reader, reply_ptr) == REDIS_ERR) {
		goto end;
	}


	if(reply->type != REDIS_REPLY_ARRAY) {
		goto end;
	}


	cmd = cmd_new(reply->elements);

	for(i = 0; i < reply->elements; ++i) {
		redisReply *ri = reply->element[i];

		switch(ri->type) {
			case REDIS_REPLY_STRING:
				cmd->argv_len[i] = ri->len;
				cmd->argv[i] = calloc(cmd->argv_len[i] + 1, 1);
				memcpy(cmd->argv[i], ri->str, ri->len);
				break;

			case REDIS_REPLY_INTEGER:
				cmd->argv_len[i] = integer_length(ri->integer);
				cmd->argv[i] = calloc(cmd->argv_len[i] + 1, 1);
				sprintf(cmd->argv[i], "%lld", ri->integer);
				break;

			default:
				cmd_free(cmd);
				cmd = NULL;
				goto end;
		}
	}


end:

	if(reader) redisReaderFree(reader);


	if(reply) freeReplyObject(reply);

	return cmd;
}
