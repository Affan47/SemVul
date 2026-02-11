mqtt3_db_message_release(struct mosquitto_db *db, struct mosquitto *context, uint16_t mid, enum mosquitto_msg_direction dir)
{
	struct mosquitto_client_msg *tail, *last = NULL;
	int qos;
	int retain;
	char *topic;
	char *source_id;
	int msg_index = 0;
	bool deleted = false;

	if(!context) return MOSQ_ERR_INVAL;

	tail = context->msgs;
	while(tail){
		msg_index++;
		if(tail->state == mosq_ms_queued && msg_index <= max_inflight){
			tail->timestamp = mosquitto_time();
			if(tail->direction == mosq_md_out){
				switch(tail->qos){
					case 0:
						tail->state = mosq_ms_publish_qos0;
						break;
					case 1:
						tail->state = mosq_ms_publish_qos1;
						break;
					case 2:
						tail->state = mosq_ms_publish_qos2;
						break;
				}
			}else{
				if(tail->qos == 2){
					_mosquitto_send_pubrec(context, tail->mid);
					tail->state = mosq_ms_wait_for_pubrel;
				}
			}
		}
		if(tail->mid == mid && tail->direction == dir){
			qos = tail->store->msg.qos;
			topic = tail->store->msg.topic;
			retain = tail->retain;
			source_id = tail->store->source_id;


			if(!topic || !mqtt3_db_messages_queue(db, source_id, topic, qos, retain, tail->store)){
				_message_remove(context, &tail, last);
				deleted = true;
			}else{
				return 1;
			}
		}else{
			last = tail;
			tail = tail->next;
		}
		if(msg_index > max_inflight && deleted){
			return MOSQ_ERR_SUCCESS;
		}
	}
	if(deleted){
		return MOSQ_ERR_SUCCESS;
	}else{
		return 1;
	}
}
