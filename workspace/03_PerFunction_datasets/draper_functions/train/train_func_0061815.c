TentativelyDefineElementN(Dtd dtd,
					    const Char *name, int namelen)
{
#ifdef FOR_LT
    static struct element_definition e;
    RHTEntry *entry;

    if (!(entry = DeclareElement(dtd->doctype, name, namelen, 0, (ctVals)CT_any))) {
      return NULL;
    };
    e.doctype = dtd->doctype;
    e.name = (Char *)dtd->doctype->elements+entry->keyptr;
    e.elsum = (NSL_ElementSummary_I *)(dtd->doctype->permanentBase+entry->eval);

    e.elsum->omitStart |= 2;
    return &e;
#else
    ElementDefinition e;

    if(!(e = Malloc(sizeof(*e))) || !(name = Strndup(name, namelen)))
	return 0;

    e->tentative = 1;
    e->name = name;
    e->namelen = namelen;
    e->type = CT_any;
    e->content = 0;
    e->attributes = 0;
    e->next = dtd->elements;
    dtd->elements = e;

    return e;
#endif
}
