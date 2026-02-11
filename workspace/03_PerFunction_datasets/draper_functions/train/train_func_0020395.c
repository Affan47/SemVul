sqlite_db_filename(pTHX_ SV *dbh)
{
    D_imp_dbh(dbh);
    const char *filename;

    croak_if_db_is_null();

    filename = sqlite3_db_filename(imp_dbh->db, "main");
    return filename ? newSVpv(filename, 0) : &PL_sv_undef;
}
