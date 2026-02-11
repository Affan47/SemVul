deriveClusters(Agraph_t* dg, Agraph_t * g)
{
    Agraph_t *subg;
    Agnode_t *dn;
    Agnode_t *n;

    for (subg = agfstsubg(g); subg; subg = agnxtsubg(subg)) {
	if (!strncmp(agnameof(subg), "cluster", 7)) {
	    dn = agnode(dg, agnameof(subg), 1);
	    agbindrec (dn, "nodeinfo", sizeof(Agnodeinfo_t), TRUE);
	    ND_ptr(dn) = (Agobj_t*)subg;
	    for (n = agfstnode(subg); n; n = agnxtnode(subg, n)) {
		if (ND_ptr(n)) {
		   fprintf (stderr, "Error: node \"%s\" belongs to two non-nested clusters \"%s\" and \"%s\"\n",
			agnameof (n), agnameof(subg), agnameof(ND_dn(n)));
		}
		ND_ptr(n) = (Agobj_t*)dn;
	    }
	}
	else {
	    deriveClusters (dg, subg);
	}
    }
}
