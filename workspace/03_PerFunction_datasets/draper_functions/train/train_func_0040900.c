dfs(Agraph_t * g, Agnode_t * n, Agraph_t * out, char *marks)
{
    Agedge_t *e;
    Agnode_t *other;

    MARK(n) = 1;
    agsubnode(out,n,1);
    for (e = agfstedge(g, n); e; e = agnxtedge(g, e, n)) {
	if ((other = agtail(e)) == n)
	    other = aghead(e);
	if (!MARK(other))
	    dfs(g, other, out, marks);
    }
}
