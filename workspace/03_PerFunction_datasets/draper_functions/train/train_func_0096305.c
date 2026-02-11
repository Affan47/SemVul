mysql_list_realm_options(u08bits *realm) {
  int ret = -1;
	donot_print_connection_success = 1;
	char statement[TURN_LONG_STRING_SIZE];
	MYSQL * myc = get_mydb_connection();
	if(myc) {
		if(realm && realm[0]) {
			snprintf(statement,sizeof(statement),"select realm,opt,value from turn_realm_option where realm='%s' order by realm,opt",realm);
		} else {
			snprintf(statement,sizeof(statement),"select realm,opt,value from turn_realm_option order by realm,opt");
		}
		int res = mysql_query(myc, statement);
		if(res) {
			TURN_LOG_FUNC(TURN_LOG_LEVEL_ERROR, "Error retrieving MySQL DB information: %s\n",mysql_error(myc));
		} else {
			MYSQL_RES *mres = mysql_store_result(myc);
			if(!mres) {
				TURN_LOG_FUNC(TURN_LOG_LEVEL_ERROR, "Error retrieving MySQL DB information: %s\n",mysql_error(myc));
			} else if(mysql_field_count(myc)!=3) {
				TURN_LOG_FUNC(TURN_LOG_LEVEL_ERROR, "Unknown error retrieving MySQL DB information: %s\n",statement);
			} else {
				for(;;) {
					MYSQL_ROW row = mysql_fetch_row(mres);
					if(!row) {
						break;
					} else {
						if(row[0] && row[1] && row[2]) {
							printf("%s[%s]=%s\n",row[1],row[0],row[2]);
						}
					}
				}
        ret = 0;
			}

			if(mres)
				mysql_free_result(mres);
		}
	}
  return ret;
}
