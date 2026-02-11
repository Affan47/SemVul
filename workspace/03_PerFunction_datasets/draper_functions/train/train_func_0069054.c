openDatabase()
{
#if defined(HAVE_SQLITE3_H)
    int rc;


    if (! get_read_write_mode()) {

	rc = sqlite3_open_v2(get_database_filename().c_str(),
			     &db,
			     SQLITE_OPEN_READONLY,
			     NULL);
    } else {

	rc = sqlite3_open_v2(get_database_filename().c_str(),
			     &db,
			     SQLITE_OPEN_READWRITE,
			     NULL);
    }


    if (rc != SQLITE_OK) {

	rc = sqlite3_open_v2(get_database_filename().c_str(),
			     &db,
			     SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,
			     NULL);


	if (rc != SQLITE_OK) {
	    std::string error = sqlite3_errmsg(db);
	    logger << ERROR << "Unable to open database: " << get_database_filename() << endl;
	    throw SqliteDatabaseConnectorException(PRESAGE_SQLITE_OPEN_DATABASE_ERROR, error);
	} else {
	    logger << WARN << "Creating new language model database: " << get_database_filename() << endl;
	}


	for (size_t cardinality = 1;
	     cardinality <= get_cardinality ();
	     cardinality++)
	{
	    createNgramTable(cardinality);
	}
    }

#elif defined(HAVE_SQLITE_H)
    char* errormsg = 0;
    db = sqlite_open(get_database_filename().c_str(), 0, &errormsg);
    if (db == 0) {
	std::string error;
	if (errormsg != 0) {
	    error = errormsg;
	}
#ifdef HAVE_STDLIB_H
        free(errormsg);
#endif
	logger << ERROR << "Unable to open database: " << get_database_filename() << " : " << endl;
	throw SqliteDatabaseConnectorException(error);
    }
#endif


}
