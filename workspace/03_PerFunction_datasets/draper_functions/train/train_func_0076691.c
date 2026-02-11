httpsqs_maxqueue(struct sqs_queue_status* st, uint32_t httpsqs_input_num) {
	if( st->count > httpsqs_input_num ) return 0;
	return st->maxqueue = httpsqs_input_num;
}
