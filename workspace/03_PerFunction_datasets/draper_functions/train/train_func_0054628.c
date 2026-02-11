init_database_connector_if_ready ()
{


    if (! dbfilename.empty()
        && cardinality > 0
        && learn_mode_set ) {

        delete db;

        if (dbloglevel.empty ()) {

	    db = new SqliteDatabaseConnector(dbfilename,
					     cardinality,
					     wanna_learn);
        } else {

            db = new SqliteDatabaseConnector(dbfilename,
					     cardinality,
					     wanna_learn,
					     dbloglevel);
        }
    }
}
