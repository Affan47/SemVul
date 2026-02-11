dispatch_app_message(env, msg)
	ENV *env;
	REPMGR_MESSAGE *msg;
{
	DB_REP *db_rep;
	DB_CHANNEL db_channel;
	CHANNEL channel;
	__repmgr_msg_metadata_args meta;
	DBT *dbt, *segment;
	u_int32_t flags, i, size, *uiptr;
	u_int8_t *data;
	void *ptr;
	int ret;

	COMPQUIET(size, 0);

	db_rep = env->rep_handle;

	db_channel.channel = &channel;
	db_channel.send_msg = __repmgr_send_response;


	db_channel.close = __repmgr_channel_close_inval;
	db_channel.send_request = __repmgr_send_request_inval;
	db_channel.set_timeout = __repmgr_channel_timeout_inval;

	channel.msg = msg;
	channel.env = env;
	channel.c.conn = msg->v.appmsg.conn;
	channel.responded = FALSE;
	channel.meta = &meta;


	dbt = &msg->v.appmsg.buf;
	data = dbt->data;
	dbt->size -= __REPMGR_MSG_METADATA_SIZE;
	ret = __repmgr_msg_metadata_unmarshal(env,
	    &meta, &data[dbt->size], __REPMGR_MSG_METADATA_SIZE, NULL);
	DB_ASSERT(env, ret == 0);

	dbt->ulen = dbt->size;
	DB_MULTIPLE_INIT(ptr, dbt);
	for (i = 0; i < APP_MSG_SEGMENT_COUNT(msg->msg_hdr); i++) {
		segment = &msg->v.appmsg.segments[i];
		uiptr = ptr;
		*uiptr = ntohl(*uiptr);
		uiptr[-1] = ntohl(uiptr[-1]);
		DB_MULTIPLE_NEXT(ptr, dbt, data, size);
		DB_ASSERT(env, data != NULL);
		DB_INIT_DBT(*segment, data, size);
	}

	flags = F_ISSET(&meta, REPMGR_REQUEST_MSG_TYPE) ?
	    DB_REPMGR_NEED_RESPONSE : 0;

	if (db_rep->msg_dispatch == NULL) {
		__db_errx(env, DB_STR("3670",
	    "No message dispatch call-back function has been configured"));
		if (F_ISSET(channel.meta, REPMGR_REQUEST_MSG_TYPE))
			return (__repmgr_send_err_resp(env,
			    &channel, DB_NOSERVER));
		else
			return (0);
	}

	(*db_rep->msg_dispatch)(env->dbenv,
	    &db_channel, &msg->v.appmsg.segments[0],
	    APP_MSG_SEGMENT_COUNT(msg->msg_hdr), flags);

	if (F_ISSET(channel.meta, REPMGR_REQUEST_MSG_TYPE) &&
	    !channel.responded) {
		__db_errx(env, DB_STR("3671",
		    "Application failed to provide a response"));
		return (__repmgr_send_err_resp(env, &channel, DB_KEYEMPTY));
	}

	return (0);
}
