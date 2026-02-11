loadOrders(mcGraph * mcg, int cacheId)
{
    mcNode *n;
    mcLevel *l;
    int id = 0;
    int idx;
    for (idx = 0; idx < mcg->lvl_cnt; idx++) {
	l = mcg->lvls[idx];
	for (id = 0; id < l->nodecnt; id++) {
	    n = l->nodes[id];
	    n->order = n->prevOrder[cacheId];
	}
    }
    for (idx = 0; idx < mcg->lvl_cnt; idx++) {
	l = mcg->lvls[idx];
	reOrderLevel(l);
	normalizeLevel(l);
    }
}
