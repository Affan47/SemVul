result_to_json(MYSQL_RES * myresult, apr_pool_t *mpool) {
	MYSQL_FIELD *fields;
	json_value *result = json_create_object(mpool);
	unsigned int num_fields;
	unsigned int i;
	num_fields = mysql_num_fields(myresult);
	fields = mysql_fetch_fields(myresult);
	json_value *header = json_create_array(mpool, num_fields);
	json_add_object(result, "HEADER", header);
	json_value *coltypes = json_create_array(mpool, num_fields);
	json_add_object(result, "TYPES", coltypes);
	for (i = 0; i < num_fields; i++) {
		json_append_array(header, json_create_string(mpool, fields[i].name));
		json_append_array(coltypes, json_create_string(mpool, field_to_string(
				fields[i], mpool)));

		json_value *rows = json_create_array(mpool, SLAYER_MAX_ROWS);
		json_add_object(result, "ROWS", rows);
		MYSQL_ROW myrow;
		while ( (myrow = mysql_fetch_row(myresult)) !=NULL) {
			json_value *orow = json_create_array(mpool, num_fields);
			json_append_array(rows, orow);

			for (i = 0; i < num_fields; i++) {
				json_append_array(orow, col_to_json(fields[i], myrow[i], mpool));
			}
		}
	}
	return result;
}
