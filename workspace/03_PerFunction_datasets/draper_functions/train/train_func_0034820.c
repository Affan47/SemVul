_ar_pgsql_check_password(authreg_t ar, char *username, char *realm, char password[257])
{
    pgsqlcontext_t ctx = (pgsqlcontext_t) ar->private;
    PGconn *conn = ctx->conn;

    char iuser[PGSQL_LU+1], irealm[PGSQL_LR+1], ipassword[PGSQL_LR+1];
    char euser[PGSQL_LU*2+1], erealm[PGSQL_LR*2+1], epassword[PGSQL_LR*2+1], sql[1024+PGSQL_LU*2+PGSQL_LR*2+1+PGSQL_LR*2+1];
    PGresult *res;

    snprintf(iuser, PGSQL_LU+1, "%s", username);
    snprintf(irealm, PGSQL_LR+1, "%s", realm);
    snprintf(ipassword, PGSQL_LR+1, "%s", password);

    PQescapeString(euser, iuser, strlen(iuser));
    PQescapeString(erealm, irealm, strlen(irealm));
    PQescapeString(epassword, ipassword, strlen(ipassword));

    sprintf(sql, ctx->sql_check_password, euser, epassword, erealm);

    log_debug(ZONE, "prepared sql: %s", sql);

    res = PQexec(conn, sql);
    if(PQresultStatus(res) != PGRES_TUPLES_OK && PQstatus(conn) != CONNECTION_OK) {
        log_write(ar->c2s->log, LOG_ERR, "pgsql: lost connection to database, attempting reconnect");
        PQclear(res);
        PQreset(conn);
        if(PQstatus(conn) != CONNECTION_OK) {
            log_write(ar->c2s->log, LOG_ERR, "pgsql: connection to database failed, will retry later: %s", PQerrorMessage(conn));
            return 1;
        }

        res = PQexec(conn, sql);
    }
    if(PQresultStatus(res) != PGRES_TUPLES_OK) {
        log_write(ar->c2s->log, LOG_ERR, "pgsql: sql select failed: %s", PQresultErrorMessage(res));
        PQclear(res);
        return 1;
    }

    if(PQntuples(res) != 1) {
        log_write(ar->c2s->log, LOG_ERR, "pgsql: Empty result");
        PQclear(res);
        return 1;
    }

    int retval = 1;

    if(PQgetisnull(res, 0, 0)) {
        log_debug(ZONE, "pgsql: check_password returns NULL");
        PQclear(res);
        return 1;
    }

    const char *result = PQgetvalue(res, 0, 0);
    log_debug(ZONE, "pgsql:  check_password result: '%s'", result);

    if (strcmp("0", result) != 0) {

        retval = 0;
    } else {
        retval = 1;
    }

    PQclear(res);

    return retval;
}
