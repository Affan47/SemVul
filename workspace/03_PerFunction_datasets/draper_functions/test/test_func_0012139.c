odbc_release_obj2(struct odbc_obj *obj, struct odbc_txn_frame *tx)
{
	SQLINTEGER nativeerror=0, numfields=0;
	SQLSMALLINT diagbytes=0, i;
	unsigned char state[10], diagnostic[256];

	ast_debug(2, "odbc_release_obj2(%p) called (obj->txf = %p)\n", obj, obj->txf);
	if (tx) {
		ast_debug(1, "called on a transactional handle with %s\n", tx->forcecommit ? "COMMIT" : "ROLLBACK");
		if (SQLEndTran(SQL_HANDLE_DBC, obj->con, tx->forcecommit ? SQL_COMMIT : SQL_ROLLBACK) == SQL_ERROR) {

			SQLGetDiagField(SQL_HANDLE_DBC, obj->con, 1, SQL_DIAG_NUMBER, &numfields, SQL_IS_INTEGER, &diagbytes);
			for (i = 0; i < numfields; i++) {
				SQLGetDiagRec(SQL_HANDLE_DBC, obj->con, i + 1, state, &nativeerror, diagnostic, sizeof(diagnostic), &diagbytes);
				ast_log(LOG_WARNING, "SQLEndTran returned an error: %s: %s\n", state, diagnostic);
				if (!strcmp((char *)state, "25S02") || !strcmp((char *)state, "08007")) {


					SQLEndTran(SQL_HANDLE_DBC, obj->con, SQL_ROLLBACK);
				}
				if (i > 10) {
					ast_log(LOG_WARNING, "Oh, that was good.  There are really %d diagnostics?\n", (int)numfields);
					break;
				}
			}
		}


		if (SQLSetConnectAttr(obj->con, SQL_ATTR_AUTOCOMMIT, (void *)SQL_AUTOCOMMIT_ON, 0) == SQL_ERROR) {
			SQLGetDiagField(SQL_HANDLE_DBC, obj->con, 1, SQL_DIAG_NUMBER, &numfields, SQL_IS_INTEGER, &diagbytes);
			for (i = 0; i < numfields; i++) {
				SQLGetDiagRec(SQL_HANDLE_DBC, obj->con, i + 1, state, &nativeerror, diagnostic, sizeof(diagnostic), &diagbytes);
				ast_log(LOG_WARNING, "SetConnectAttr (Autocommit) returned an error: %s: %s\n", state, diagnostic);
				if (i > 10) {
					ast_log(LOG_WARNING, "Oh, that was good.  There are really %d diagnostics?\n", (int)numfields);
					break;
				}
			}
		}
	}

#ifdef DEBUG_THREADS
	obj->file[0] = '\0';
	obj->function[0] = '\0';
	obj->lineno = 0;
#endif


	obj->used = 0;
	if (obj->txf) {

		obj->txf->obj = NULL;
		obj->txf = release_transaction(obj->txf);
	}
	ao2_ref(obj, -1);
}
