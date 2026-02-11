open_db(DB **db, const char *name, int type)
{
    int ret;
    ret = db_create(db, OVDBenv, 0);
    if (ret != 0) {
	warn("db_create failed: %s\n", db_strerror(ret));
	return ret;
    }
    ret = (*db)->open(*db, NULL, name, NULL, type, DB_CREATE, 0666);
    if (ret != 0) {
	(*db)->close(*db, 0);
        warn("%s->open failed: %s", name, db_strerror(ret));
	return ret;
    }
    return 0;
}
