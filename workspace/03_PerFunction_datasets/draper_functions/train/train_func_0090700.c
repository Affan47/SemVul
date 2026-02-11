alloc_cursor()
{
    cursor *c;
    SQLRETURN ret;
    char msg[OD_MSG];
    char *emsg = NULL;
    SQLINTEGER err;


    c = (cursor *) db_malloc(sizeof(cursor));
    if (c == NULL) {
	report_error("allocate cursor");
	return c;
    }

    ret = SQLAllocHandle(SQL_HANDLE_STMT, ODconn, &c->stmt);
    if ((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO)) {
	SQLGetDiagRec(SQL_HANDLE_DBC, ODconn, 1, NULL, &err, msg, sizeof(msg),
		      NULL);
	G_asprintf(&emsg, "AllocStatement()\n%s (%d)\n", msg, (int)err);
	report_error(emsg);
	G_free(emsg);

	return c;
    }


    c->token = db_new_token(c);
    if (c->token < 0) {
	free_cursor(c);
	c = NULL;
	report_error("db_new_token()");
    }

    return c;
}
