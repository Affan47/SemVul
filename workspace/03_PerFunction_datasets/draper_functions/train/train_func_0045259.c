kdbSet_hosts(KDB *handle, KeySet *returned, const Key *parentKey)
{
	int errnosave = errno;
	ssize_t nr_keys = 0, nr_alias = 0;
	FILE *fp;
	Key *key, *alias=0;
	char * lastline;

	if (strcmp (keyName(kdbhGetMountpoint(handle)), keyName(parentKey))) return 0;

	fp = fopen (kdbhGetBackendData(handle), "w");

	if (fp == 0)
	{

		errno = errnosave;
		return -1;
	}

	kdbbWriteLock (fp);

	ksRewind (returned);
	key = ksNext (returned);

	nr_keys ++;

	while (1)
	{
		if (!alias) key = ksNext (returned);
		else key = alias;
		if (!key) break;

		lastline = strrchr (keyComment(key), '\n');
		if (lastline)
		{
			*lastline = '\0';
			fprintf (fp, "%s\n", keyComment(key));
			*lastline = '\n';
		}

		fprintf (fp, "%s\t%s", (char*)keyValue(key), (char*)keyBaseName (key));

		nr_alias = 0;
		if (keyIsDir (key))
		{
			while ((alias = ksNext (returned)) != 0)
			{
				if (keyIsDir(alias)) break;
				if (strncmp (keyName(key), keyName(alias), strlen(keyName(key)))) break;;
				if (strlen(keyName(key)) + strlen (keyBaseName (alias)) + 1 != strlen (keyName(alias))) goto error;
				if (strncmp (keyBaseName (alias), "alias", 5)) goto error;
				fprintf (fp, "\t%s", (char*)keyValue (alias));
				nr_alias++;
			}
		} else alias = 0;

		if (lastline)
		{
			if (*(lastline+1) != '\0') fprintf (fp, " #%s", lastline+1);
		} else {
			if (*keyComment(key) != '\0') fprintf (fp, " #%s", keyComment(key));
		}

		fprintf (fp, "\n");
		nr_keys += nr_alias + 1;
	}

	kdbbUnlock (fp);
	fclose (fp);
	errno = errnosave;
	return nr_keys;

error:
	kdbbUnlock (fp);
	fclose (fp);

	fp = fopen ("/tmp/hosts", "w");
	fclose (fp);
	errno = errnosave;
	return -1;
}
