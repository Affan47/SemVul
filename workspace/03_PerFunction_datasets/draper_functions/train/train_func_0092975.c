sqlite2_db_STORE_attrib (SV *dbh, imp_dbh_t *imp_dbh, SV *keysv, SV *valuesv)
{
    dTHR;
    char *key = SvPV_nolen(keysv);
    char *errmsg;
    int retval;

    if (strEQ(key, "AutoCommit")) {
        if (SvTRUE(valuesv)) {

            if ( (!DBIc_is(imp_dbh, DBIcf_AutoCommit)) && (imp_dbh->in_tran) ) {
	        if ((retval = sqlite_exec(imp_dbh->db, "COMMIT TRANSACTION",
					  NULL, NULL, &errmsg)
		     != SQLITE_OK))
                {
		    sqlite2_error(dbh, (imp_xxh_t*)imp_dbh, retval, errmsg);
                    sqlite_freemem(errmsg);
                    return TRUE;
                }
                imp_dbh->in_tran = FALSE;
            }
        }
        DBIc_set(imp_dbh, DBIcf_AutoCommit, SvTRUE(valuesv));
        return TRUE;
    }
    else if (strEQ(key, "sqlite_no_utf8_flag") || strEQ(key, "NoUTF8Flag")) {
        warn("NoUTF8Flag is deprecated due to perl unicode weirdness\n");
        if (SvTRUE(valuesv)) {
            imp_dbh->no_utf8_flag = TRUE;
        }
        else {
            imp_dbh->no_utf8_flag = FALSE;
        }
        return TRUE;
    }
    else if (strEQ(key, "sqlite_handle_binary_nulls")) {
        if (SvTRUE(valuesv)) {
          imp_dbh->handle_binary_nulls = TRUE;
        }
        else {
          imp_dbh->handle_binary_nulls = FALSE;
        }
        return TRUE;
    }
    return FALSE;
}
