appendnode(char *name, char *port, char *sport)
{
	item		*elt;

	if (sport) {
		port = concatPort (port, sport);
	}
	elt = cons_node(agnode(S->g,name,TRUE),port);
	listapp(&(S->nodelist),elt);
	agstrfree(G,name);
}
