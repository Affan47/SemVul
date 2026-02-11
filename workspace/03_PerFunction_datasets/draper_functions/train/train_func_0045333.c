get_loadable_libraries(void)
{
	PGresult  **ress;
	int			totaltups;
	int			dbnum;
	bool		found_public_plpython_handler = false;

	ress = (PGresult **) pg_malloc(old_cluster.dbarr.ndbs * sizeof(PGresult *));
	totaltups = 0;


	for (dbnum = 0; dbnum < old_cluster.dbarr.ndbs; dbnum++)
	{
		DbInfo	   *active_db = &old_cluster.dbarr.dbs[dbnum];
		PGconn	   *conn = connectToServer(&old_cluster, active_db->db_name);


		ress[dbnum] = executeQueryOrDie(conn,
										"SELECT DISTINCT probin "
										"FROM	pg_catalog.pg_proc "
										"WHERE	prolang = 13 /* C */ AND "
										"probin IS NOT NULL AND "
										"oid >= %u;",
										FirstNormalObjectId);
		totaltups += PQntuples(ress[dbnum]);


		if (GET_MAJOR_VERSION(old_cluster.major_version) < 901)
		{
			PGresult   *res;

			res = executeQueryOrDie(conn,
									"SELECT 1 "
						   "FROM	pg_catalog.pg_proc JOIN pg_namespace "
							 "		ON pronamespace = pg_namespace.oid "
							   "WHERE proname = 'plpython_call_handler' AND "
									"nspname = 'public' AND "
									"prolang = 13 /* C */ AND "
									"probin = '$libdir/plpython' AND "
									"pg_proc.oid >= %u;",
									FirstNormalObjectId);
			if (PQntuples(res) > 0)
			{
				if (!found_public_plpython_handler)
				{
					pg_log(PG_WARNING,
						   "\nThe old cluster has a \"plpython_call_handler\" function defined\n"
						   "in the \"public\" schema which is a duplicate of the one defined\n"
						   "in the \"pg_catalog\" schema.  You can confirm this by executing\n"
						   "in psql:\n"
						   "\n"
						   "    \\df *.plpython_call_handler\n"
						   "\n"
						   "The \"public\" schema version of this function was created by a\n"
						   "pre-8.1 install of plpython, and must be removed for pg_upgrade\n"
						   "to complete because it references a now-obsolete \"plpython\"\n"
						   "shared object file.  You can remove the \"public\" schema version\n"
					   "of this function by running the following command:\n"
						   "\n"
						 "    DROP FUNCTION public.plpython_call_handler()\n"
						   "\n"
						   "in each affected database:\n"
						   "\n");
				}
				pg_log(PG_WARNING, "    %s\n", active_db->db_name);
				found_public_plpython_handler = true;
			}
			PQclear(res);
		}

		PQfinish(conn);
	}

	if (found_public_plpython_handler)
		pg_fatal("Remove the problem functions from the old cluster to continue.\n");


	os_info.libraries = (char **) pg_malloc(totaltups * sizeof(char *));


	totaltups = 0;

	for (dbnum = 0; dbnum < old_cluster.dbarr.ndbs; dbnum++)
	{
		PGresult   *res = ress[dbnum];
		int			ntups;
		int			rowno;

		ntups = PQntuples(res);
		for (rowno = 0; rowno < ntups; rowno++)
		{
			char	   *lib = PQgetvalue(res, rowno, 0);
			bool		dup = false;
			int			n;

			for (n = 0; n < totaltups; n++)
			{
				if (strcmp(lib, os_info.libraries[n]) == 0)
				{
					dup = true;
					break;
				}
			}
			if (!dup)
				os_info.libraries[totaltups++] = pg_strdup(lib);
		}

		PQclear(res);
	}

	os_info.num_libraries = totaltups;

	pg_free(ress);
}
