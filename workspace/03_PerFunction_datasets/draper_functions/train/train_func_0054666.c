objectList(edge_t * ep, expand_t* pm)
{
    node_t *h = aghead(ep);
    node_t *t = agtail(ep);
    graph_t *hg = PARENT(h);
    graph_t *tg = PARENT(t);
    int hlevel;
    int tlevel;
    void *hex;
    void *tex;
    objlist *list = NEW(objlist);


    if (IS_CLUST_NODE(h)) {
	hex = hg;
	hg = GPARENT(hg);
    } else
	hex = h;
    if (IS_CLUST_NODE(t)) {
	tex = tg;
	tg = GPARENT(tg);
    } else
	tex = t;

    hlevel = LEVEL(hg);
    tlevel = LEVEL(tg);
    if (hlevel > tlevel) {
	raiseLevel(list, hlevel, hex, tlevel, &hg, pm);
	hex = hg;
	hg = GPARENT(hg);
    } else if (tlevel > hlevel) {
	raiseLevel(list, tlevel, tex, hlevel, &tg, pm);
	tex = tg;
	tg = GPARENT(tg);
    }


    while (hg != tg) {
	addGraphObjs(list, hg, NULL, hex, pm);
	addGraphObjs(list, tg, tex, NULL, pm);
	hex = hg;
	hg = GPARENT(hg);
	tex = tg;
	tg = GPARENT(tg);
    }
    addGraphObjs(list, tg, tex, hex, pm);

    return list;
}
