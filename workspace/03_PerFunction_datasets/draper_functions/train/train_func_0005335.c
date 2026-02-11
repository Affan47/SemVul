levenFunc(
	sqlite3_context *context,
	int argc,
	sqlite3_value **argv
){
	int result;

	if ( sqlite3_value_type( argv[0] ) == SQLITE_NULL || sqlite3_value_type( argv[1] ) == SQLITE_NULL ){
		sqlite3_result_null( context );
		return;
	}

	result = levenshtein_distance(
		(char*) sqlite3_value_text( argv[0] ),
		(char*) sqlite3_value_text( argv[1] )
	);

	if ( result == -1 ){

		sqlite3_result_null( context );
                return;
	}

	sqlite3_result_int( context, result );
}
