TentativelyDefineNotationN(Dtd dtd,
					      const Char *name, int namelen)
{
    NotationDefinition n;

    if(!(n = Malloc(sizeof(*n))) || !(name = Strndup(name, namelen)))
	return 0;

    n->name = name;
    n->tentative = 1;
    n->systemid = 0;
    n->publicid = 0;
    n->next = dtd->notations;
    dtd->notations = n;

    return n;
}
