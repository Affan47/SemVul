conn_sslcons_close() {
	struct conn_sslcon *ccon;
	struct conn_sslcon *ncon;
	for(ccon = conn_sslcons; ccon; ccon = ncon) {
		ncon = ccon->next;
		conn_sslcon_free(ccon);
		free(ccon);
	}
}
