_sys_update_memory(struct mosquitto_db *db, char *buf)
{
	static unsigned long current_heap = -1;
	static unsigned long max_heap = -1;
	unsigned long value_ul;

	value_ul = _mosquitto_memory_used();
	if(current_heap != value_ul){
		current_heap = value_ul;
		snprintf(buf, BUFLEN, "%lu", current_heap);
		mqtt3_db_messages_easy_queue(db, NULL, "$SYS/broker/heap/current", 2, strlen(buf), buf, 1);
	}
	value_ul =_mosquitto_max_memory_used();
	if(max_heap != value_ul){
		max_heap = value_ul;
		snprintf(buf, BUFLEN, "%lu", max_heap);
		mqtt3_db_messages_easy_queue(db, NULL, "$SYS/broker/heap/maximum", 2, strlen(buf), buf, 1);
	}
}
