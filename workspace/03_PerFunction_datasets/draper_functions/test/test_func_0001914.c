lcp_cilen(f)
    fsm *f;
{
    lcp_options *go = &lcp_gotoptions[f->unit];

#define LENCIVOID(neg)	(neg ? CILEN_VOID : 0)
#define LENCICHAP(neg)	(neg ? CILEN_CHAP : 0)
#define LENCISHORT(neg)	(neg ? CILEN_SHORT : 0)
#define LENCILONG(neg)	(neg ? CILEN_LONG : 0)
#define LENCILQR(neg)	(neg ? CILEN_LQR: 0)


    return (LENCISHORT(go->neg_mru) +
	    LENCILONG(go->neg_asyncmap) +
	    LENCICHAP(go->neg_chap) +
	    LENCISHORT(!go->neg_chap && go->neg_upap) +
	    LENCILQR(go->neg_lqr) +
	    LENCILONG(go->neg_magicnumber) +
	    LENCIVOID(go->neg_pcompression) +
	    LENCIVOID(go->neg_accompression));
}
