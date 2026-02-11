_reconnectToDB(ArchiveHandle *AH, const char *dbname)
{
	if (RestoringToDB(AH))
		ReconnectToServer(AH, dbname, NULL);
	else
	{
		PQExpBuffer qry = createPQExpBuffer();

		appendPQExpBuffer(qry, "\\connect %s\n\n",
						  dbname ? fmtId(dbname) : "-");
		ahprintf(AH, "%s", qry->data);
		destroyPQExpBuffer(qry);
	}


	if (AH->currUser)
		free(AH->currUser);

	AH->currUser = strdup("");


	if (AH->currSchema)
		free(AH->currSchema);
	AH->currSchema = strdup("");
	AH->currWithOids = -1;


	_doSetFixedOutputState(AH);
}
