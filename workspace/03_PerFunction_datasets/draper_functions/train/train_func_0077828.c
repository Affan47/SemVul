search_component(graph_t * g, node_t * n)
{
    int c, i;
    elist vec[4];
    node_t *other;
    edge_t *e;

    Agedge_t* tempE;
    static int count=0;

    add_to_component(n);
    vec[0] = ND_out(n);
    vec[1] = ND_in(n);
    vec[2] = ND_flat_out(n);
    vec[3] = ND_flat_in(n);

    for (e = agfstout(g, n); e; e = agnxtout(g, e))
    {
	Agedge_t* tempE=e;
	if ((other = aghead(e)) == n)
	    other = agtail(e);
	if (ND_mark(other) != Cmark)
        	search_component(g, other);
	e=tempE;
    }
    for (e = agfstin(g, n); e; e = agnxtin(g, e))
    {

	count++;
	if(count ==53)
	    printf("dgfdg");
	if ((other = aghead(e)) == n)
	    other = agtail(e);
	if (ND_mark(other) != Cmark)
        	search_component(g, other);
	tempE=e;
    }


}
