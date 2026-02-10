gv_graph_state(GVJ_t *job, graph_t *g)
{
    int j;
    Agsym_t *a;
    gv_argvlist_t *list;

    list = &(job->selected_obj_type_name);
    j = 0;
    if (g == agroot(g)) {
	if (agisdirected(g))
            gv_argvlist_set_item(list, j++, s_digraph);
	else
            gv_argvlist_set_item(list, j++, s_graph);
    }
    else {
        gv_argvlist_set_item(list, j++, s_subgraph);
    }
    gv_argvlist_set_item(list, j++, agnameof(g));
    list->argc = j;

    list = &(job->selected_obj_attributes);
    a = NULL;
    while ((a = agnxtattr(g, AGRAPH, a))) {
        gv_argvlist_set_item(list, j++, a->name);
        gv_argvlist_set_item(list, j++, agxget(g, a));
        gv_argvlist_set_item(list, j++, (char*)GVATTR_STRING);
    }
    list->argc = j;

    a = agfindgraphattr(g, s_href);
    if (!a)
	a = agfindgraphattr(g, s_URL);
    if (a)
	job->selected_href = strdup_and_subst_obj(agxget(g, a), (void*)g);
}
