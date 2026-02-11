open_env(const char* env_home, u_int32_t set_flags1,
    u_int32_t oflags, u_int32_t cachesize, int mode, u_int32_t cflags)
{
	int ret;

	DbEnv *penv = new DbEnv(cflags | DB_CXX_NO_EXCEPTIONS);
	if (set_flags1)
		BDBOP(penv->set_flags(set_flags1, 1), ret);
	BDBOP(penv->set_cachesize(0, cachesize, 1), ret);
	BDBOP(penv->set_lk_max_lockers(2000), ret);
	BDBOP(penv->set_lk_max_locks(2000), ret);
	BDBOP(penv->set_lk_max_objects(2000), ret);
	BDBOP2(penv->open(env_home, oflags, mode), ret, penv->close(0));

	stack<DbTxn*> stk;
	DbTxn *ptxn = NULL;
	if (oflags & DB_INIT_CDB) {
		BDBOP2(penv->cdsgroup_begin(&ptxn), ret, ptxn->commit(0));
		stk.push(ptxn);
	}

	env_txns_.insert(make_pair(penv, stk));
	global_lock(mtx_handle_);
	open_envs_.insert(make_pair(penv, 1u));
	delenvs.insert(penv);
	global_unlock(mtx_handle_);
	return penv;
}
