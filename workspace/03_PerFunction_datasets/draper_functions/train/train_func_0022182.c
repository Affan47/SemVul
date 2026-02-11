ipcp_rejci(f, p, len)
    fsm *f;
    u_char *p;
    int len;
{
    ipcp_options *go = &ipcp_gotoptions[f->unit];
    u_char cimaxslotindex, ciflag, cilen;
    u_short cishort;
    u_int32_t cilong;
    ipcp_options try;

    try = *go;


#define REJCIADDR(opt, neg, old, val1, val2) \
    if (go->neg && \
	len >= (cilen = old? CILEN_ADDRS: CILEN_ADDR) && \
	p[1] == cilen && \
	p[0] == opt) { \
	u_int32_t l; \
	len -= cilen; \
	INCPTR(2, p); \
	GETLONG(l, p); \
	cilong = htonl(l); \
	 \
	if (cilong != val1) \
	    goto bad; \
	if (old) { \
	    GETLONG(l, p); \
	    cilong = htonl(l); \
	     \
	    if (cilong != val2) \
		goto bad; \
	} \
	try.neg = 0; \
    }

#define REJCIVJ(opt, neg, val, old, maxslot, cflag) \
    if (go->neg && \
	p[1] == (old? CILEN_COMPRESS : CILEN_VJ) && \
	len >= p[1] && \
	p[0] == opt) { \
	len -= p[1]; \
	INCPTR(2, p); \
	GETSHORT(cishort, p); \
	  \
	if (cishort != val) \
	    goto bad; \
	if (!old) { \
	   GETCHAR(cimaxslotindex, p); \
	   if (cimaxslotindex != maxslot) \
	     goto bad; \
	   GETCHAR(ciflag, p); \
	   if (ciflag != cflag) \
	     goto bad; \
        } \
	try.neg = 0; \
     }

    REJCIADDR((go->old_addrs? CI_ADDRS: CI_ADDR), neg_addr,
	      go->old_addrs, go->ouraddr, go->hisaddr);

    REJCIVJ(CI_COMPRESSTYPE, neg_vj, go->vj_protocol, go->old_vj,
	    go->maxslotindex, go->cflag);


    if (len != 0)
	goto bad;


    if (f->state != OPENED)
	*go = try;
    return 1;

bad:
    IPCPDEBUG((LOG_INFO, "ipcp_rejci: received bad Reject!"));
    return 0;
}
