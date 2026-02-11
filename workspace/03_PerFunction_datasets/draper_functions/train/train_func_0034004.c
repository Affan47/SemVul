sqlite_db_login6(SV *dbh, imp_dbh_t *imp_dbh, char *dbname, char *user, char *pass, SV *attr)
{
    dTHX;
    int rc;

    sqlite_trace(dbh, imp_dbh, 3, form("login '%s' (version %s)", dbname, sqlite3_version));

    rc = sqlite_open(dbname, &(imp_dbh->db));
    if ( rc != SQLITE_OK ) {
        return FALSE;
    }
    DBIc_IMPSET_on(imp_dbh);

    imp_dbh->unicode                   = FALSE;
    imp_dbh->functions                 = newAV();
    imp_dbh->aggregates                = newAV();
    imp_dbh->collation_needed_callback = newSVsv( &PL_sv_undef );
    imp_dbh->timeout                   = SQL_TIMEOUT;
    imp_dbh->handle_binary_nulls       = FALSE;
    imp_dbh->allow_multiple_statements = FALSE;
    imp_dbh->use_immediate_transaction = TRUE;
    imp_dbh->see_if_its_a_number       = FALSE;

    sqlite3_busy_timeout(imp_dbh->db, SQL_TIMEOUT);

#if 0


    sqlite_exec(dbh, "PRAGMA foreign_keys = ON");
#endif

#if 0


    sqlite_exec(dbh, "PRAGMA reverse_unordered_selects = ON");
#endif

    DBIc_ACTIVE_on(imp_dbh);

    return TRUE;
}
