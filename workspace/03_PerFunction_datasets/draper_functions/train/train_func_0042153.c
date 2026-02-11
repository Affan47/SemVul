gvLayoutJobs(GVC_t * gvc, Agraph_t * g)
{
    gvlayout_engine_t *gvle;
    char *p;
    int rc;

    agbindrec(g, "Agraphinfo_t", sizeof(Agraphinfo_t), TRUE);
    GD_gvc(g) = gvc;
    if (g != agroot(g))
	GD_gvc(agroot(g)) = gvc;

    if ((p = agget(g, "layout"))) {
        gvc->layout.engine = NULL;
	rc = gvlayout_select(gvc, p);
	if (rc == NO_SUPPORT) {
	    agerr (AGERR, "Layout type: \"%s\" not recognized. Use one of:%s\n",
	        p, gvplugin_list(gvc, API_layout, p));
	    return -1;
	}
    }

    gvle = gvc->layout.engine;
    if (! gvle)
	return -1;

    gv_fixLocale (1);
    graph_init(g, gvc->layout.features->flags & LAYOUT_USES_RANKDIR);
    GD_drawing(agroot(g)) = GD_drawing(g);
    if (gvle && gvle->layout) {
	gvle->layout(g);


	if (gvle->cleanup)
	    GD_cleanup(g) = gvle->cleanup;
    }
    gv_fixLocale (0);
    return 0;
}
