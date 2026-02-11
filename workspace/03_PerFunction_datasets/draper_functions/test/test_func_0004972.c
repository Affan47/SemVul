dns_srv_parser( unsigned char* msg, unsigned char* end,
								  unsigned char* rdata)
{
	struct srv_rdata* srv;
	int len;

	srv=0;
	if ((rdata+6)>=end) goto error;
	srv=(struct srv_rdata*)local_malloc(sizeof(struct srv_rdata));
	if (srv==0){
		LM_ERR("out of pkg memory\n");
		goto error;
	}

	memcpy((void*)&srv->priority, rdata, 2);
	memcpy((void*)&srv->weight,   rdata+2, 2);
	memcpy((void*)&srv->port,     rdata+4, 2);
	rdata+=6;
	srv->priority=ntohs(srv->priority);
	srv->weight=ntohs(srv->weight);
	srv->port=ntohs(srv->port);
	if ((len=dn_expand(msg, end, rdata, srv->name, MAX_DNS_NAME-1))==-1)
		goto error;

	return srv;
error:
	if (srv) local_free(srv);
	return 0;
}
