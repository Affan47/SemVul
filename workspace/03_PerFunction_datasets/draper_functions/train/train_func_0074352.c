agdictof(Agraph_t * g, int kind)
{
    Agdatadict_t *dd;
    Dict_t *dict;

    dd = agdatadict(g, FALSE);
    if (dd)
	switch (kind) {
	case AGRAPH:
	    dict = dd->dict.g;
	    break;
	case AGNODE:
	    dict = dd->dict.n;
	    break;
	case AGINEDGE:
	case AGOUTEDGE:
	    dict = dd->dict.e;
	    break;
	default:
	    agerr(AGERR,"agdictof: unknown kind %d\n", kind);
	    dict = NIL(Dict_t *);
	    break;
    } else
	dict = NIL(Dict_t *);
    return dict;
}
