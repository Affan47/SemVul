errdetail_busy_db(int notherbackends, int npreparedxacts)
{


	if (notherbackends > 0 && npreparedxacts > 0)
		errdetail("There are %d other session(s) and %d prepared transaction(s) using the database.",
				  notherbackends, npreparedxacts);
	else if (notherbackends > 0)
		errdetail("There are %d other session(s) using the database.",
				  notherbackends);
	else
		errdetail("There are %d prepared transaction(s) using the database.",
				  npreparedxacts);
	return 0;
}
