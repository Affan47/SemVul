SearchStmtCache(const char *ecpgQuery)
{
	int			entNo,
				entIx;


	entNo = HashStmt(ecpgQuery);


	for (entIx = 0; entIx < stmtCacheEntPerBucket; ++entIx)
	{
		if (stmtCacheEntries[entNo].stmtID[0])
		{
			if (!strcmp(ecpgQuery, stmtCacheEntries[entNo].ecpgQuery))
				break;
		}
		++entNo;
	}


	if (entIx >= stmtCacheEntPerBucket)
		entNo = 0;

	return (entNo);
}
