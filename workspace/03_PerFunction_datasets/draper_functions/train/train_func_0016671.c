__dbreg_open_file(env, txn, argp, info)
	ENV *env;
	DB_TXN *txn;
	__dbreg_register_args *argp;
	void *info;
{
	DB *dbp;
	DB_ENTRY *dbe;
	DB_LOG *dblp;
	u_int32_t id, opcode, status;
	int ret;

	dblp = env->lg_handle;
	opcode = FLD_ISSET(argp->opcode, DBREG_OP_MASK);


	MUTEX_LOCK(env, dblp->mtx_dbreg);
	if (argp->fileid != DB_LOGFILEID_INVALID &&
	    argp->fileid < dblp->dbentry_cnt)
		dbe = &dblp->dbentry[argp->fileid];
	else
		dbe = NULL;

	if (dbe != NULL) {
		if (dbe->deleted) {
			MUTEX_UNLOCK(env, dblp->mtx_dbreg);
			return (ENOENT);
		}


		if ((dbp = dbe->dbp) != NULL) {
			if (opcode == DBREG_REOPEN ||
			    opcode == DBREG_XREOPEN ||
			    !F_ISSET(dbp, DB_AM_OPEN_CALLED) ||
			    dbp->meta_pgno != argp->meta_pgno ||
			    argp->name.size == 0 ||
			    memcmp(dbp->fileid, argp->uid.data,
			    DB_FILE_ID_LEN) != 0) {
				MUTEX_UNLOCK(env, dblp->mtx_dbreg);
				(void)__dbreg_revoke_id(dbp, 0,
				    DB_LOGFILEID_INVALID);
				if (F_ISSET(dbp, DB_AM_RECOVER))
					(void)__db_close(dbp, NULL, DB_NOSYNC);
				goto reopen;
			}

			DB_ASSERT(env, dbe->dbp == dbp);
			MUTEX_UNLOCK(env, dblp->mtx_dbreg);


			if (argp != NULL && argp->id != TXN_INVALID &&
			    (ret = __db_txnlist_update(env, info,
			    argp->id, TXN_EXPECTED, NULL, &status, 1)) != 0)
				return (ret);
			return (0);
		}
	}

	MUTEX_UNLOCK(env, dblp->mtx_dbreg);

reopen:


	if (argp->name.size == 0) {
		(void)__dbreg_add_dbentry(env, dblp, NULL, argp->fileid);
		return (ENOENT);
	}


	if (txn != NULL) {
		id = txn->txnid;
		memset(txn, 0, sizeof(DB_TXN));
		txn->txnid = id;
		txn->mgrp = env->tx_handle;
	}

	return (__dbreg_do_open(env,
	    txn, dblp, argp->uid.data, argp->name.data, argp->ftype,
	    argp->fileid, argp->meta_pgno, info, argp->id, opcode));
}
