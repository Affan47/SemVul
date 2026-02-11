calc_load(struct mosquitto_db *db, char *buf, const char *topic, double exponent, double interval, double *current)
{
	double new_value;

	new_value = interval + exponent*((*current) - interval);
	if(fabs(new_value - (*current)) >= 0.01){
		snprintf(buf, BUFLEN, "%.2f", new_value);
		mqtt3_db_messages_easy_queue(db, NULL, topic, 2, strlen(buf), buf, 1);
	}
	(*current) = new_value;
}
