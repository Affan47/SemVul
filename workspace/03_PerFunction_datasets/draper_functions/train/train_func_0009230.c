get_ticket_realm(isc_mem_t *mctx) {
	krb5_context ctx;
	krb5_error_code rc;
	krb5_ccache ccache;
	krb5_principal princ;
	char *name, *ticket_realm;

	rc = krb5_init_context(&ctx);
	if (rc != 0)
		return;

	rc = krb5_cc_default(ctx, &ccache);
	if (rc != 0) {
		krb5_free_context(ctx);
		return;
	}

	rc = krb5_cc_get_principal(ctx, ccache, &princ);
	if (rc != 0) {
		krb5_cc_close(ctx, ccache);
		krb5_free_context(ctx);
		return;
	}

	rc = krb5_unparse_name(ctx, princ, &name);
	if (rc != 0) {
		krb5_free_principal(ctx, princ);
		krb5_cc_close(ctx, ccache);
		krb5_free_context(ctx);
		return;
	}

	ticket_realm = strrchr(name, '@');
	if (ticket_realm != NULL) {
		realm = isc_mem_strdup(mctx, ticket_realm);
	}

	free(name);
	krb5_free_principal(ctx, princ);
	krb5_cc_close(ctx, ccache);
	krb5_free_context(ctx);
	if (realm != NULL && debugging)
		fprintf(stderr, "Found realm from ticket: %s\n", realm+1);
}
