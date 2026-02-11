fetchKerbTicket(imp_dbh_t *imp_dbh) {
	dTHX;

	if (imp_dbh->kerbGetTicket) {
		dSP;
		SV *retval;
		int count;
		char *server = imp_dbh->server;

		if (!*server) {
			char *s = getenv("DSQUERY");
			if (s && *s) {
				server = s;
			} else {
				server = "SYBASE";
			}
		}

		ENTER;
		SAVETMPS;
		PUSHMARK(sp);

		XPUSHs(sv_2mortal(newSVpv(server, 0)));

		PUTBACK;
		if ((count = perl_call_sv(imp_dbh->kerbGetTicket, G_SCALAR)) != 1)
			croak("A Kerberos Ticket handler can't return a LIST.");
		SPAGAIN;
		retval = POPs;

		PUTBACK;
		FREETMPS;
		LEAVE;

		if (SvPOK(retval)) {
			strncpy(imp_dbh->kerberosPrincipal, SvPVX(retval), 255);
			imp_dbh->kerberosPrincipal[31] = 0;
		}
	}
}
