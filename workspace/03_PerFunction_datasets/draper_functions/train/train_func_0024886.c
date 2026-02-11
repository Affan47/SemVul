mgs_set_client_ca_file(cmd_parms * parms, void *dummy,
				   const char *arg)
{
	int rv;
	const char *file;
	apr_pool_t *spool;
	gnutls_datum_t data;

	mgs_srvconf_rec *sc =
	    (mgs_srvconf_rec *) ap_get_module_config(parms->server->
						     module_config,
						     &gnutls_module);
	apr_pool_create(&spool, parms->pool);

	file = ap_server_root_relative(spool, arg);

	if (load_datum_from_file(spool, file, &data) != 0) {
		return apr_psprintf(parms->pool, "GnuTLS: Error Reading "
				    "Client CA File '%s'", file);
	}

	sc->ca_list_size = INIT_CA_SIZE;
	sc->ca_list = malloc(sc->ca_list_size * sizeof(*sc->ca_list));
	if (sc->ca_list == NULL) {
		return apr_psprintf(parms->pool,
				    "mod_gnutls: Memory allocation error");
	}

	rv = gnutls_x509_crt_list_import(sc->ca_list, &sc->ca_list_size,
					 &data, GNUTLS_X509_FMT_PEM,
					 GNUTLS_X509_CRT_LIST_IMPORT_FAIL_IF_EXCEED);
	if (rv < 0 && rv != GNUTLS_E_SHORT_MEMORY_BUFFER) {
		return apr_psprintf(parms->pool, "GnuTLS: Failed to load "
				    "Client CA File '%s': (%d) %s", file,
				    rv, gnutls_strerror(rv));
	}

	if (INIT_CA_SIZE < sc->ca_list_size) {
		sc->ca_list =
		    realloc(sc->ca_list,
			    sc->ca_list_size * sizeof(*sc->ca_list));
		if (sc->ca_list == NULL) {
			return apr_psprintf(parms->pool,
					    "mod_gnutls: Memory allocation error");
		}


		rv = gnutls_x509_crt_list_import(sc->ca_list,
						 &sc->ca_list_size, &data,
						 GNUTLS_X509_FMT_PEM, 0);

		if (rv < 0) {
			return apr_psprintf(parms->pool,
					    "GnuTLS: Failed to load "
					    "Client CA File '%s': (%d) %s",
					    file, rv, gnutls_strerror(rv));
		}
	}

	apr_pool_destroy(spool);
	return NULL;
}
