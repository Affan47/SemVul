_ar_pgsql_get_password(authreg_t ar, char *username, char *realm, char password[257]) {
    pgsqlcontext_t ctx = (pgsqlcontext_t) ar->private;
    PGresult *res = _ar_pgsql_get_user_tuple(ar, username, realm);
    int fpass;

    if(res == NULL)
        return 1;

    fpass = PQfnumber(res, ctx->field_password);
    if(fpass == -1) {
        log_debug(ZONE, "weird, password field wasn't returned");
        PQclear(res);
        return 1;
    }

    if(PQgetisnull(res, 0, fpass)) {
        PQclear(res);
        return 1;
    }

    strcpy(password, PQgetvalue(res, 0, fpass));

    PQclear(res);

    return 0;
}
