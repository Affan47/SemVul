findcache(db)
    char *db;
{
    char *scan;
    int i;


    if (!strncmp(db, PRIVPREFIX, PRIVPREFIXLEN) && db[PRIVPREFIXLEN] == '/') {


	scan = strchr(db + PRIVPREFIXLEN + 1, '/');
	if (scan == NULL) return (NULL);
	++scan;


	for (i = 0; privdbstr[i]; ++i) {

	    if (!strcmp(scan, privdbstr[i]) ||
		(i >= PDBPREFIXPOS
		 && !strncmp(scan, privdbstr[i], strlen(privdbstr[i])))) {


		if (strcmp(privdb[i].db + PREFIXLEN + 1, db)) {
		    if (privdb[i].locks > 0) return (NULL);
		    if (privdb[i].modified) {
			writecache(&privdb[i]);
		    }
		    freecache(&privdb[i]);
		    snprintf(privdb[i].db, sizeof(privdb[i].db), "%s/%s", PREFIX, db);
		}
		return (&privdb[i]);
	    }
	}
	return (NULL);
    }
    for (i = 0; globdbstr[i]; ++i) {
	if (!strcmp(db, globdbstr[i])) {
	    snprintf(globdb[i].db, sizeof(globdb[i].db), "%s/%s", PREFIX, db);
	    return (&globdb[i]);
	}
    }
    return (NULL);
}
