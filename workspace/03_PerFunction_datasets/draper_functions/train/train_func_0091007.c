php_sqlite_open(char *filename, int mode, char *persistent_id, zval *return_value, zval *errmsg, zval *object TSRMLS_DC)
{
	char *errtext = NULL;
	sqlite *sdb = NULL;
	struct php_sqlite_db *db = NULL;

	sdb = sqlite_open(filename, mode, &errtext);

	if (sdb == NULL) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "%s", errtext);

		if (errmsg) {
			ZVAL_STRING(errmsg, errtext, 1);
		}

		sqlite_freemem(errtext);


		if (object && Z_TYPE_P(object) != IS_OBJECT) {
			RETVAL_NULL();
		} else {
			RETVAL_FALSE;
		}
		return NULL;
	}

	db = (struct php_sqlite_db *)pemalloc(sizeof(struct php_sqlite_db), persistent_id ? 1 : 0);
	db->is_persistent = persistent_id ? 1 : 0;
	db->last_err_code = SQLITE_OK;
	db->db = sdb;

	zend_hash_init(&db->callbacks, 0, NULL, php_sqlite_callback_dtor, db->is_persistent);


	sqlite_create_function(sdb, "php", -1, php_sqlite_generic_function_callback, 0);


	sqlite_busy_timeout(sdb, 60000);


	if (PG(safe_mode) || (PG(open_basedir) && *PG(open_basedir))) {
		sqlite_set_authorizer(sdb, php_sqlite_authorizer, NULL);
	}

	db->rsrc_id = ZEND_REGISTER_RESOURCE(object ? NULL : return_value, db, persistent_id ? le_sqlite_pdb : le_sqlite_db);
	if (object) {

		if (Z_TYPE_P(object) != IS_OBJECT) {
			sqlite_instanciate(sqlite_ce_db, object TSRMLS_CC);
		}

		SQLITE_REGISTER_OBJECT(db, object, db)
	}

	if (persistent_id) {
		zend_rsrc_list_entry le;

		Z_TYPE(le) = le_sqlite_pdb;
		le.ptr = db;

		if (FAILURE == zend_hash_update(&EG(persistent_list), persistent_id,
					strlen(persistent_id)+1,
					(void *)&le, sizeof(le), NULL)) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Failed to register persistent resource");
		}
	}

	return db;
}
