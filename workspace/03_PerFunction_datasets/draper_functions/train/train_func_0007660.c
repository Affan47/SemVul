sort_groups(LIST *glist)
{
    LIST *slist;
    GROUP **stab;
    GROUP *gp;
    int st_ix;


    stab = calloc(LIST_LENGTH(glist), sizeof(GROUP *));
    if (!stab)
	gupout(1, "Malloc of sort table failed");

    st_ix = 0;
    TRAVERSE(glist, gp) {
	gp->order = st_ix;
	stab[st_ix++] = gp;
    }


    qsort(stab, LIST_LENGTH(glist), sizeof(GROUP *), mat_compare);


    slist = create_list();

    for (st_ix = 0; st_ix < LIST_LENGTH(glist); st_ix++)
	add_group(slist, stab[st_ix]);

    free(stab);
    free(glist);

    return slist;
}
