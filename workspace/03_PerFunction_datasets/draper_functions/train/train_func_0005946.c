ovdb_open_berkeleydb(int mode, int flags)
{
    int ret;
    u_int32_t ai_flags = DB_INIT_LOCK|DB_INIT_LOG|DB_INIT_MPOOL|DB_INIT_TXN;

    OVDBmode = mode;
    read_ovdb_conf();

    if(OVDBenv != NULL)
	return 0;

    if(OVDBmode & OV_WRITE) {
	_db_flags |= DB_CREATE;
	ai_flags |= DB_CREATE;
    } else {
	_db_flags |= DB_RDONLY;
    }
    if(flags & OVDB_RECOVER)
	ai_flags |= DB_RECOVER;

    ret = db_env_create(&OVDBenv, 0);
    if (ret != 0) {
        warn("OVDB: db_env_create: %s", db_strerror(ret));
	return ret;
    }

    if((flags & (OVDB_UPGRADE | OVDB_RECOVER)) == (OVDB_UPGRADE | OVDB_RECOVER))
	ai_flags |= DB_PRIVATE;
    if(!(ai_flags & DB_PRIVATE)) {
	if(ovdb_conf.useshm)
	    ai_flags |= DB_SYSTEM_MEM;
	OVDBenv->set_shm_key(OVDBenv, ovdb_conf.shmkey);
    }

    OVDBenv->set_errcall(OVDBenv, OVDBerror);
    OVDBenv->set_cachesize(OVDBenv, 0, ovdb_conf.cachesize, ovdb_conf.ncache);
    OVDBenv->set_lk_max_locks(OVDBenv, ovdb_conf.maxlocks);
    OVDBenv->set_lk_max_lockers(OVDBenv, ovdb_conf.maxlocks);
    OVDBenv->set_lk_max_objects(OVDBenv, ovdb_conf.maxlocks);

    if(ovdb_conf.txn_nosync)
	OVDBenv->set_flags(OVDBenv, DB_TXN_NOSYNC, 1);

    if((flags & (OVDB_UPGRADE | OVDB_RECOVER)) != OVDB_UPGRADE) {
	ret = OVDBenv->open(OVDBenv, ovdb_conf.home, ai_flags, 0666);
	if (ret != 0) {
	    OVDBenv->close(OVDBenv, 0);
	    OVDBenv = NULL;
            warn("OVDB: OVDBenv->open: %s", db_strerror(ret));
	    return ret;
	}
    }

    return 0;
}
