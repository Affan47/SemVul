abook_deleteent(id, name, alias)
    auth_id *id;
    char *name, *alias;
{
    char *key, *scan;
    sdb_keyvalue *kv;
    int i, result, kvcount, ownerlen, keylen;
    long delta;
    char dbname[256];


    if (!(abook_rights(id, name, NULL) & ACL_DELETE)) {
	return (AB_PERM);
    }

    if ((ownerlen = abook_dbname(dbname, sizeof(dbname), name)) < 0) return (AB_FAIL);


    for (scan = alias; *scan && *scan != '*' && *scan != '%'; ++scan);
    if (*scan) return (AB_FAIL);


    if (sdb_writelock(dbname, NULL, SDB_ICASE) < 0) return (AB_FAIL);


    keylen = strlen(alias) + 3;
    key = malloc(keylen);
    if (!key) {
	sdb_unlock(dbname, NULL, SDB_ICASE);
	return (AB_FAIL);
    }
    snprintf(key, keylen, "%s\"*", alias);
    result = sdb_match(dbname, key, SDB_ICASE, NULL, 1, &kv, &kvcount);
    free(key);
    if (result < 0 || !kvcount) {
	sdb_unlock(dbname, NULL, SDB_ICASE);
	return (result < 0 ? AB_FAIL : AB_NOEXIST);
    }


    delta = (strlen(alias) + 1) * kvcount;
    for (i = 0; i < kvcount; ++i) {
	delta -= strlen(kv[i].key) + strlen(kv[i].value);
    }
    if ((result = option_doquota(auth_username(id), delta)) < 0) {
	sdb_unlock(dbname, NULL, SDB_ICASE);
	return (result);
    }


    for (i = 0; i < kvcount; ++i) {
	sdb_remove(dbname, kv[i].key, SDB_ICASE);
    }
    sdb_freematch(kv, kvcount, 0);


    if (sdb_unlock(dbname, NULL, SDB_ICASE) < 0) {
	option_doquota(auth_username(id), -delta);
	return (AB_FAIL);
    }

    return (AB_SUCCESS);
}
