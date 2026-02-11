cloneGraph(Agraph_t * tgt, Agraph_t * src)
{
    Agedge_t *e;
    Agedge_t *ne;
    Agnode_t *t;
    Agraph_t *sg;
    char* name;
    Dt_t* emap = dtopen (&edgepair, Dtoset);
    edgepair_t* data = (edgepair_t*)malloc(sizeof(edgepair_t)*agnedges(src));
    edgepair_t* ep = data;

    for (t = agfstnode(src); t; t = agnxtnode(src, t)) {
	if (!copy(tgt, OBJ(t))) {
	    exerror("error cloning node %s from graph %s",
		  agnameof(t), agnameof(src));
	}
    }
    for (t = agfstnode(src); t; t = agnxtnode(src, t)) {
	for (e = agfstout(src, t); e; e = agnxtout(src, e)) {
	    if (!(ne = (Agedge_t*)copy(tgt, OBJ(e)))) {
		name = agnameof(AGMKOUT(e));
		if (name)
		    exerror("error cloning edge (%s,%s)[%s] from graph %s",
		      agnameof(agtail(e)), agnameof(aghead(e)),
		      name, agnameof(src));
		else
		    exerror("error cloning edge (%s,%s) from graph %s",
		      agnameof(agtail(e)), agnameof(aghead(e)),
		      agnameof(src));
		return;
	    }
	    ep->key = e;
	    ep->val = ne;
	    dtinsert (emap, ep++);
	}
    }
    for (sg = agfstsubg(src); sg; sg = agnxtsubg(sg)) {
	if (!cloneSubg(tgt, sg, emap)) {
	    exerror("error cloning subgraph %s from graph %s",
		  agnameof(sg), agnameof(src));
	}
    }

    dtclose (emap);
    free (data);
}
