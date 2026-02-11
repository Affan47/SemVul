nodeByName(Agraph_t * g, char *name)
{
    Agnode_t *v;
    for (v = agfstnode(g); v; v = agnxtnode(g, v)) {
	if (strcmp(agnameof(v), name) == 0)
	    return v;
    }
    return NULL;
}
