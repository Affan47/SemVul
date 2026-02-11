locpath_search(struct locpath_trace *lpt,
                          struct tree **tmatch, struct step **smatch) {
    int last;
    int result = -1;

    for (last=lpt->maxns; last >= 0 && lpt->ns[last]->used == 0; last--);
    if (last < 0) {
        *smatch = lpt->lp->steps;
        result = 1;
        goto done;
    }
    if (lpt->ns[last]->used > 1) {
        result = -1;
        goto done;
    }
    result = 0;
    *tmatch = lpt->ns[last]->nodes[0];
    *smatch = lpt->lp->steps;
    for (int i=0; i < last; i++)
        *smatch = (*smatch)->next;
 done:
    for (int i=0; i < lpt->maxns; i++)
        free_nodeset(lpt->ns[i]);
    FREE(lpt->ns);
    return result;
}
