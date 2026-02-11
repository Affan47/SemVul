agfstin(Agraph_t * g, Agnode_t * n)
{
    Agsubnode_t *sn;
    Agedge_t *e = NILedge;

    sn = agsubrep(g, n);
	if (sn) {
		dtrestore(g->e_seq, sn->in_seq);
		e = (Agedge_t *) dtfirst(g->e_seq);
		sn->in_seq = dtextract(g->e_seq);
	}
    return e;
}
