mysql_get_oauth_key(const u08bits *kid, oauth_key_data_raw *key) {

	int ret = -1;
	char statement[TURN_LONG_STRING_SIZE];
	snprintf(statement,sizeof(statement),"select ikm_key,timestamp,lifetime,hkdf_hash_func,as_rs_alg,as_rs_key,auth_alg,auth_key from oauth_key where kid='%s'",(const char*)kid);

	MYSQL * myc = get_mydb_connection();
	if(myc) {
		int res = mysql_query(myc, statement);
		if(res) {
			TURN_LOG_FUNC(TURN_LOG_LEVEL_ERROR, "Error retrieving MySQL DB information: %s\n",mysql_error(myc));
		} else {
			MYSQL_RES *mres = mysql_store_result(myc);
			if(!mres) {
				TURN_LOG_FUNC(TURN_LOG_LEVEL_ERROR, "Error retrieving MySQL DB information: %s\n",mysql_error(myc));
			} else if(mysql_field_count(myc)!=8) {
				TURN_LOG_FUNC(TURN_LOG_LEVEL_ERROR, "Unknown error retrieving MySQL DB information: %s\n",statement);
			} else {
				MYSQL_ROW row = mysql_fetch_row(mres);
				if(row && row[0]) {
					unsigned long *lengths = mysql_fetch_lengths(mres);
					if(lengths) {
						STRCPY((char*)key->kid,kid);
						ns_bcopy(row[0],key->ikm_key,lengths[0]);
						key->ikm_key[lengths[0]]=0;

						char stimestamp[128];
						ns_bcopy(row[1],stimestamp,lengths[1]);
						stimestamp[lengths[1]]=0;
						key->timestamp = (u64bits)strtoull(stimestamp,NULL,10);

						char slifetime[128];
						ns_bcopy(row[2],slifetime,lengths[2]);
						slifetime[lengths[2]]=0;
						key->lifetime = (u32bits)strtoul(slifetime,NULL,10);

						ns_bcopy(row[3],key->hkdf_hash_func,lengths[3]);
						key->hkdf_hash_func[lengths[3]]=0;

						ns_bcopy(row[4],key->as_rs_alg,lengths[4]);
						key->as_rs_alg[lengths[4]]=0;

						ns_bcopy(row[5],key->as_rs_key,lengths[5]);
						key->as_rs_key[lengths[5]]=0;

						ns_bcopy(row[6],key->auth_alg,lengths[6]);
						key->auth_alg[lengths[6]]=0;

						ns_bcopy(row[7],key->auth_key,lengths[7]);
						key->auth_key[lengths[7]]=0;

						ret = 0;
					}
				}
			}

			if(mres)
				mysql_free_result(mres);
		}
	}
	return ret;
}
