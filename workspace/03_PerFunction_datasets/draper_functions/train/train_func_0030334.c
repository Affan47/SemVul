mqtt3_db_backup(struct mosquitto_db *db, bool cleanup, bool shutdown)
{
	int rc = 0;
	FILE *db_fptr = NULL;
	uint32_t db_version_w = htonl(MOSQ_DB_VERSION);
	uint32_t crc = htonl(0);
	dbid_t i64temp;
	uint32_t i32temp;
	uint16_t i16temp;
	uint8_t i8temp;
	char err[256];
	char *outfile = NULL;
	int len;

	if(!db || !db->config || !db->config->persistence_filepath) return MOSQ_ERR_INVAL;
	_mosquitto_log_printf(NULL, MOSQ_LOG_INFO, "Saving in-memory database to %s.", db->config->persistence_filepath);
	if(cleanup){
		mqtt3_db_store_clean(db);
	}

	len = strlen(db->config->persistence_filepath)+5;
	outfile = _mosquitto_calloc(len+1, 1);
	if(!outfile){
		_mosquitto_log_printf(NULL, MOSQ_LOG_INFO, "Error saving in-memory database, out of memory.");
		return MOSQ_ERR_NOMEM;
	}
	snprintf(outfile, len, "%s.new", db->config->persistence_filepath);
	db_fptr = _mosquitto_fopen(outfile, "wb");
	if(db_fptr == NULL){
		_mosquitto_log_printf(NULL, MOSQ_LOG_INFO, "Error saving in-memory database, unable to open %s for writing.", outfile);
		goto error;
	}


	write_e(db_fptr, magic, 15);
	write_e(db_fptr, &crc, sizeof(uint32_t));
	write_e(db_fptr, &db_version_w, sizeof(uint32_t));


	i16temp = htons(DB_CHUNK_CFG);
	write_e(db_fptr, &i16temp, sizeof(uint16_t));

	i32temp = htonl(sizeof(dbid_t) + sizeof(uint8_t) + sizeof(uint8_t));
	write_e(db_fptr, &i32temp, sizeof(uint32_t));

	i8temp = shutdown;
	write_e(db_fptr, &i8temp, sizeof(uint8_t));
	i8temp = sizeof(dbid_t);
	write_e(db_fptr, &i8temp, sizeof(uint8_t));

	i64temp = db->last_db_id;
	write_e(db_fptr, &i64temp, sizeof(dbid_t));

	if(mqtt3_db_message_store_write(db, db_fptr)){
		goto error;
	}

	mqtt3_db_client_write(db, db_fptr);
	mqtt3_db_subs_retain_write(db, db_fptr);

	fclose(db_fptr);

	if(rename(outfile, db->config->persistence_filepath) != 0){
		goto error;
	}
	_mosquitto_free(outfile);
	outfile = NULL;
	return rc;
error:
	if(outfile) _mosquitto_free(outfile);
	strerror_r(errno, err, 256);
	_mosquitto_log_printf(NULL, MOSQ_LOG_ERR, "Error: %s.", err);
	if(db_fptr) fclose(db_fptr);
	return 1;
}
