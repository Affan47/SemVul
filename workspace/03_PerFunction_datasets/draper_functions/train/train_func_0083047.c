cloneG(Agraph_t * g, char* name)
{
    Agraph_t* ng;

    if (!name || (*name == '\0'))
	name = agnameof (g);
    ng = openG(name, g->desc);
    if (ng) {
	copyAttr((Agobj_t*)g, (Agobj_t*)ng);
	cloneGraph(ng, g);
    }
    return ng;
}
