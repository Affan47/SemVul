query_putrdataset(ns_client_t *client, dns_rdataset_t **rdatasetp) {
	dns_rdataset_t *rdataset = *rdatasetp;

	CTRACE("query_putrdataset");
	if (rdataset != NULL) {
		if (dns_rdataset_isassociated(rdataset))
			dns_rdataset_disassociate(rdataset);
		dns_message_puttemprdataset(client->message, rdatasetp);
	}
	CTRACE("query_putrdataset: done");
}
