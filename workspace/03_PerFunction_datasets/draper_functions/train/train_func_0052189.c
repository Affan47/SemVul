_ar_pgsql_create_user(authreg_t ar, char *username, char *realm) {
    pgsqlcontext_t ctx = (pgsqlcontext_t) ar->private;
    PGconn *conn = ctx->conn;
    char iuser[PGSQL_LU+1], irealm[PGSQL_LR+1];
    char euser[PGSQL_LU*2+1], erealm[PGSQL_LR*2+1], sql[1024+PGSQL_LU*2+PGSQL_LR*2+1];
    PGresult *res;

    res = _ar_pgsql_get_user_tuple(ar, username, realm);
    if(res != NULL) {
        PQclear(res);
        return 1;
    }

    PQclear(res);

    snprintf(iuser, PGSQL_LU+1, "%s", username);
    snprintf(irealm, PGSQL_LR+1, "%s", realm);

    PQescapeString(euser, iuser, strlen(iuser));
    PQescapeString(erealm, irealm, strlen(irealm));

    sprintf(sql, ctx->sql_create, euser, erealm);

    log_debug(ZONE, "prepared sql: %s", sql);

    res = PQexec(conn, sql);
    if(PQresultStatus(res) != PGRES_COMMAND_OK && PQstatus(conn) != CONNECTION_OK) {
        log_write(ar->c2s->log, LOG_ERR, "pgsql: lost connection to database, attempting reconnect");
        PQclear(res);
        PQreset(conn);

        if(PQstatus(conn) != CONNECTION_OK) {
            log_write(ar->c2s->log, LOG_ERR, "pgsql: connection to database failed, will retry later: %s", PQerrorMessage(conn));
            return 1;
        }

        res = PQexec(conn, sql);
    }
    if(PQresultStatus(res) != PGRES_COMMAND_OK) {
        log_write(ar->c2s->log, LOG_ERR, "pgsql: sql insert failed: %s", PQresultErrorMessage(res));
        PQclear(res);
        return 1;
    }

    PQclear(res);

    return 0;
}
