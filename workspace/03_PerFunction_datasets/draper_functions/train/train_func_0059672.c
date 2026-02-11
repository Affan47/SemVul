ns_server_dumprecursing(ns_server_t *server) {
	FILE *fp = NULL;
	isc_result_t result;

	CHECKMF(isc_stdio_open(server->recfile, "w", &fp),
		"could not open dump file", server->recfile);
	fprintf(fp,";\n; Recursing Queries\n;\n");
	ns_interfacemgr_dumprecursing(fp, server->interfacemgr);
	fprintf(fp, "; Dump complete\n");

 cleanup:
	if (fp != NULL)
		result = isc_stdio_close(fp);
	if (result == ISC_R_SUCCESS)
		isc_log_write(ns_g_lctx, NS_LOGCATEGORY_GENERAL,
			      NS_LOGMODULE_SERVER, ISC_LOG_INFO,
			      "dumprecursing complete");
	else
		isc_log_write(ns_g_lctx, NS_LOGCATEGORY_GENERAL,
			      NS_LOGMODULE_SERVER, ISC_LOG_ERROR,
			      "dumprecursing failed: %s",
			      dns_result_totext(result));
	return (result);
}
