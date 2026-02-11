circomps(Agraph_t * g, int *cnt)
{
    int c_cnt;
    Agraph_t **ccs;
    Agraph_t *dg;
    Agnode_t *n, *v, *dt, *dh;
    Agedge_t *e;
    Agraph_t *sg;
    int i;
    Agedge_t *ep;
    Agnode_t *p;

    dg = agopen("derived", Agstrictundirected,NIL(Agdisc_t *));
    agbindrec (dg, "info", sizeof(Agraphinfo_t), TRUE);
    GD_alg(g) = dg;

    for (v = agfstnode(g); v; v = agnxtnode(g, v)) {
	if (DNODE(v))
	    continue;
	n = makeDerivedNode(dg, agnameof(v), 1, v);
	DNODE(v) = n;
    }

    for (v = agfstnode(g); v; v = agnxtnode(g, v)) {
	for (e = agfstout(g, v); e; e = agnxtout(g, e)) {
	    dt = DNODE(agtail(e));
	    dh = DNODE(aghead(e));
	    if (dt != dh) {
		agbindrec(agedge(dg, dt, dh, NULL, 1), "Agedgeinfo_t", sizeof(Agedgeinfo_t), TRUE);
	    }
	}
    }

    ccs = ccomps(dg, &c_cnt, 0);


    for (i = 0; i < c_cnt; i++) {
	sg = ccs[i];


	for (n = agfstnode(sg); n; n = agnxtnode(sg, n)) {
	    p = ORIGN(n);
	    for (e = agfstout(g, p); e; e = agnxtout(g, e)) {

		dh = DNODE(aghead(e));
		if (n != dh) {
		    ep = agedge(dg, n, dh, NULL, 1);
		    agbindrec(ep, "Agedgeinfo_t", sizeof(Agedgeinfo_t), TRUE);
		    agsubedge(sg,ep,1);
		}
	    }
	}
    }


    for (n = agfstnode(dg); n; n = agnxtnode(dg, n)) {
	for (e = agfstout(dg, n); e; e = agnxtout(dg, e)) {
	    ED_alg(e) = NEW(edata);
	}
    }

    *cnt = c_cnt;
    return ccs;
}
