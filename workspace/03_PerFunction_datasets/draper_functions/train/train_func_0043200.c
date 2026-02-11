ovdb_getartinfo(const char *group, ARTNUM artnum, TOKEN *token)
{
    int ret, cdb = 0;
    group_id_t cgid = 0;
    DB *db;
    DBT key, val;
    struct ovdata ovd;
    struct datakey dk;
    struct groupinfo gi;
    int pass = 0;

    if(clientmode) {
	struct rs_cmd rs;
	struct rs_artinfo repl;

	rs.what = CMD_ARTINFO;
	rs.grouplen = strlen(group)+1;
	rs.artlo = artnum;

	if (csend(&rs, sizeof(rs)) < 0)
            return false;
	if (csend(group, rs.grouplen) < 0)
            return false;
	crecv(&repl, sizeof(repl));

	if(repl.status != CMD_ARTINFO)
	    return false;

	if(token)
	    *token = repl.token;

	return true;
    }

    while(1) {
        ret = ovdb_getgroupinfo(group, &gi, true, NULL, 0);
	switch (ret)
        {
	case 0:
	    break;
	case DB_NOTFOUND:
	    return false;
	default:
            warn("OVDB: ovdb_getgroupinfo failed: %s", db_strerror(ret));
	    return false;
	}

	if(pass) {


	    if(cdb == gi.current_db && cgid == gi.current_gid)
		return false;
	}

	db = get_db_bynum(gi.current_db);
	if(db == NULL)
	    return false;

	memset(&dk, 0, sizeof dk);
	dk.groupnum = gi.current_gid;
	dk.artnum = htonl((u_int32_t)artnum);

	memset(&key, 0, sizeof key);
	memset(&val, 0, sizeof val);

	key.data = &dk;
	key.size = sizeof dk;


        val.flags = DB_DBT_PARTIAL;

        if(token)
            val.dlen = sizeof(struct ovdata);

	switch(ret = db->get(db, NULL, &key, &val, 0)) {
	case 0:
	case DB_NOTFOUND:
	    break;
	default:
            warn("OVDB: getartinfo: db->get: %s", db_strerror(ret));
	    return false;
	}

	if(ret == DB_NOTFOUND) {


	    if(!pass && (gi.status & GROUPINFO_MOVING)) {
		cdb = gi.current_db;
		cgid = gi.current_gid;
		pass++;
		continue;
	    }
	    return false;
	}
	break;
    }

    if(token && val.size < sizeof(struct ovdata)) {
        warn("OVDB: getartinfo: data too short");
	return false;
    }

    if(token) {
	memcpy(&ovd, val.data, sizeof(struct ovdata));
	*token = ovd.token;
    }
    return true;
}
