tcldot_layout(GVC_t *gvc, Agraph_t * g, char *engine)
{
    char buf[256];
    Agsym_t *a;
    int rc;

    gvFreeLayout(gvc, g);


    if (!engine || *engine == '\0') {
	if (agisdirected(g))
	    rc = gvlayout_select(gvc, "dot");
	else
	    rc = gvlayout_select(gvc, "neato");
    }
    else {
	if (strcasecmp(engine, "nop") == 0) {
	    Nop = 2;
	    PSinputscale = POINTS_PER_INCH;
	    rc = gvlayout_select(gvc, "neato");
	}
	else {
	    rc = gvlayout_select(gvc, engine);
	}
	if (rc == NO_SUPPORT)
	    rc = gvlayout_select(gvc, "dot");
    }
    if (rc == NO_SUPPORT) {
        fprintf(stderr, "Layout type: \"%s\" not recognized. Use one of:%s\n",
                engine, gvplugin_list(gvc, API_layout, engine));
        return;
    }
    gvLayoutJobs(gvc, g);


    if (GD_drawing(g)->landscape)
	sprintf(buf, "%d %d %d %d",
		ROUND(GD_bb(g).LL.y), ROUND(GD_bb(g).LL.x),
		ROUND(GD_bb(g).UR.y), ROUND(GD_bb(g).UR.x));
    else
	sprintf(buf, "%d %d %d %d",
		ROUND(GD_bb(g).LL.x), ROUND(GD_bb(g).LL.y),
		ROUND(GD_bb(g).UR.x), ROUND(GD_bb(g).UR.y));
    if (!(a = agattr(g, AGRAPH, "bb", NULL)))
	a = agattr(g, AGRAPH, "bb", "");
    agxset(g, a, buf);
}
