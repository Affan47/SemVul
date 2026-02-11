_db_client_msg_restore(struct mosquitto_db *db, const char *client_id, uint16_t mid, uint8_t qos, uint8_t retain, uint8_t direction, uint8_t state, uint8_t dup, uint64_t store_id)
{
	struct mosquitto_client_msg *cmsg;
	struct mosquitto_msg_store *store;
	struct mosquitto *context;

	cmsg = _mosquitto_calloc(1, sizeof(struct mosquitto_client_msg));
	if(!cmsg){
		_mosquitto_log_printf(NULL, MOSQ_LOG_ERR, "Error: Out of memory.");
		return MOSQ_ERR_NOMEM;
	}

	cmsg->store = NULL;
	cmsg->mid = mid;
	cmsg->qos = qos;
	cmsg->retain = retain;
	cmsg->direction = direction;
	cmsg->state = state;
	cmsg->dup = dup;

	store = db->msg_store;
	while(store){
		if(store->db_id == store_id){
			cmsg->store = store;
			cmsg->store->ref_count++;
			break;
		}
		store = store->next;
	}
	if(!cmsg->store){
		_mosquitto_free(cmsg);
		_mosquitto_log_printf(NULL, MOSQ_LOG_ERR, "Error restoring persistent database, message store corrupt.");
		return 1;
	}
	context = _db_find_or_add_context(db, client_id, 0);
	if(!context){
		_mosquitto_free(cmsg);
		_mosquitto_log_printf(NULL, MOSQ_LOG_ERR, "Error restoring persistent database, message store corrupt.");
		return 1;
	}
	if(context->msgs){
		context->last_msg->next = cmsg;
	}else{
		context->msgs = cmsg;
	}
	cmsg->next = NULL;
	context->last_msg = cmsg;

	return MOSQ_ERR_SUCCESS;
}
