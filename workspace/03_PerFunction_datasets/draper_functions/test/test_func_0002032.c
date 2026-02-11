gv_edge_state(GVJ_t *job, edge_t *e)
{
    int j;
    Agsym_t *a;
    Agraph_t *g;
    gv_argvlist_t *nlist, *alist;

    nlist = &(job->selected_obj_type_name);


    j = 0;
    gv_argvlist_set_item(nlist, j++, s_edge);
    gv_argvlist_set_item(nlist, j++, agnameof(agtail(e)));
    j++;
    gv_argvlist_set_item(nlist, j++, agisdirected(agraphof(agtail(e)))?"->":"--");
    gv_argvlist_set_item(nlist, j++, agnameof(aghead(e)));
    j++;
    j++;
    nlist->argc = j;

    alist = &(job->selected_obj_attributes);
    g = agroot(agraphof(aghead(e)));
    a = NULL;
    while ((a = agnxtattr(g, AGEDGE, a))) {


        if (strcmp(a->name,s_tailport) == 0)
	    gv_argvlist_set_item(nlist, 2, agxget(e, a));
	else if (strcmp(a->name,s_headport) == 0)
	    gv_argvlist_set_item(nlist, 5, agxget(e, a));


	else if (strcmp(a->name,s_key) == 0) {
	    gv_argvlist_set_item(nlist, 6, agxget(e, a));
	    continue;
	}

        gv_argvlist_set_item(alist, j++, a->name);
        gv_argvlist_set_item(alist, j++, agxget(e, a));
    }
    alist->argc = j;

    a = agfindedgeattr(agraphof(aghead(e)), s_href);
    if (!a)
	a = agfindedgeattr(agraphof(aghead(e)), s_URL);
    if (a)
	job->selected_href = strdup_and_subst_obj(agxget(e, a), (void*)e);
}
