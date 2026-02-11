agrelabel_node(Agnode_t * n, char *newname)
{
    Agraph_t *g;
    unsigned long new_id;

    g = agroot(agraphof(n));
    if (agfindnode_by_name(g, newname))
	return FAILURE;
    if (agmapnametoid(g, AGNODE, newname, &new_id, TRUE)) {
	if (agfindnode_by_id(agroot(g), new_id) == NILnode) {
	    agfreeid(g, AGNODE, AGID(n));
	    agapply(g, (Agobj_t *) n, (agobjfn_t) dict_relabel,
		    (void *) &new_id, FALSE);
	    return SUCCESS;
	} else {
	    agfreeid(g, AGNODE, new_id);
	}

    }
    return FAILURE;
}
