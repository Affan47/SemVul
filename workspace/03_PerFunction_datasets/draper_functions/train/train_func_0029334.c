server_update_lease(struct in_addr *srvaddr,
	u_char *hwaddr, unsigned long xid,
	struct in_addr *clientip, unsigned long renew,
	unsigned int status) {
    server_t		*s;
    lease_t		*l;

    if ((s=get_server(srvaddr))!=NULL) {
	if ((l=server_find_lease(s,hwaddr,xid))!=NULL){
	    memcpy(&(l->addr.s_addr),&(clientip->s_addr),IP_ADDR_LEN);
	    l->since=(unsigned long)time(NULL);
	    if (renew!=0) {


		l->renew=(unsigned long)time(NULL)+renew;
		if (cfg.verbose>=2)
		    printf("\rRenewal is in %lu secs\n",
			    (unsigned long)(l->renew)-(unsigned long)time(NULL));
	    } else {

		l->renew=(unsigned long)time(NULL)+60;
	    }
	    l->status=status;
	    if (cfg.verbose) {
		printf("Updated lease %s",inet_ntoa(*clientip));
		printf(" from server %s\n",inet_ntoa(*srvaddr));
	    }
	} else {
	    if (cfg.verbose)
		printf("Unknown lease from server %s\n",inet_ntoa(*srvaddr));
	}
    } else {
	if (cfg.verbose)
	    printf("Unknown server %s\n",inet_ntoa(*srvaddr));
    }
}
