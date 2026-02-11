_check_database_version(ArchiveHandle *AH, bool ignoreVersion)
{
	int			myversion;
	const char *remoteversion_str;
	int			remoteversion;

	myversion = _parse_version(AH, PG_VERSION);

	remoteversion_str = PQparameterStatus(AH->connection, "server_version");
	if (!remoteversion_str)
		die_horribly(AH, modulename, "could not get server_version from libpq\n");

	remoteversion = _parse_version(AH, remoteversion_str);

	AH->public.remoteVersionStr = strdup(remoteversion_str);
	AH->public.remoteVersion = remoteversion;

	if (myversion != remoteversion
		&& (remoteversion < AH->public.minRemoteVersion ||
			remoteversion > AH->public.maxRemoteVersion))
	{
		write_msg(NULL, "server version: %s; %s version: %s\n",
				  remoteversion_str, progname, PG_VERSION);
		if (ignoreVersion)
			write_msg(NULL, "proceeding despite version mismatch\n");
		else
			die_horribly(AH, NULL, "aborting because of version mismatch  (Use the -i option to proceed anyway.)\n");
	}
}
