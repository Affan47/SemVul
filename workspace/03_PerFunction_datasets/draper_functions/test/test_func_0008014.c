mqtt3_db_subs_retain_write(struct mosquitto_db *db, FILE *db_fptr)
{
	struct _mosquitto_subhier *subhier;

	subhier = db->subs.children;
	while(subhier){
		_db_subs_retain_write(db, db_fptr, subhier, "");
		subhier = subhier->next;
	}

	return MOSQ_ERR_SUCCESS;
}
