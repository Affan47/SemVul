display_header(imp_dbh_t *imp_dbh, CS_INT numcols,
		CS_DATAFMT *columns) {
	dTHX;
	CS_INT i;
	CS_INT l;
	CS_INT j;
	CS_INT disp_len;

	sv_catpv(DBIc_ERRSTR(imp_dbh), "\n");
	for (i = 0; i < numcols; i++) {
		disp_len = display_dlen(&columns[i]);
		sv_catpv(DBIc_ERRSTR(imp_dbh), columns[i].name);
		l = disp_len - strlen(columns[i].name);
		for (j = 0; j < l; j++) {
			sv_catpv(DBIc_ERRSTR(imp_dbh), " ");
		}
	}
	sv_catpv(DBIc_ERRSTR(imp_dbh), "\n");
	for (i = 0; i < numcols; i++) {
		disp_len = display_dlen(&columns[i]);
		l = disp_len - 1;
		for (j = 0; j < l; j++) {
			sv_catpv(DBIc_ERRSTR(imp_dbh), "-");
		}
		sv_catpv(DBIc_ERRSTR(imp_dbh), " ");
	}
	sv_catpv(DBIc_ERRSTR(imp_dbh), "\n");

	return CS_SUCCEED;
}
