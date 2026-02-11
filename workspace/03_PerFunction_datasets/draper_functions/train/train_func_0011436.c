mysql_auth_ping(void * rch) {
	UNUSED_ARG(rch);
	donot_print_connection_success = 1;
	MYSQL * myc = get_mydb_connection();
	if(myc) {
		char statement[TURN_LONG_STRING_SIZE];
		STRCPY(statement,"select value from turn_secret");
		int res = mysql_query(myc, statement);
		if(res) {
			TURN_LOG_FUNC(TURN_LOG_LEVEL_ERROR, "Error retrieving MySQL DB information: %s\n",mysql_error(myc));
		} else {
			MYSQL_RES *mres = mysql_store_result(myc);
			if(!mres) {
				TURN_LOG_FUNC(TURN_LOG_LEVEL_ERROR, "Error retrieving MySQL DB information: %s\n",mysql_error(myc));
			} else {
				mysql_free_result(mres);
			}
		}
	}
}
