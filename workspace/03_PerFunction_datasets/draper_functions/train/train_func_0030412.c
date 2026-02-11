aginternalmaplookup(Agraph_t * g, int objtype, char *str,
			unsigned long *result)
{
    Dict_t *d;
    IMapEntry_t *sym, template;
    char *search_str;

    if (objtype == AGINEDGE)
	objtype = AGEDGE;
    if ((d = g->clos->lookup_by_name[objtype])) {
	if ((search_str = agstrbind(g, str))) {
	    template.str = search_str;
	    sym = (IMapEntry_t *) dtsearch(d, &template);
	    if (sym) {
		*result = sym->id;
		return TRUE;
	    }
	}
    }
    return FALSE;
}
