tallyrec(struct nrec *r, struct nrec *h)
{
    struct trec *t;
    for (t=r->rlink; t; t=t->rlink)
	if (t->linkid==h)
	    return t;
    t=wmalloc(sizeof(struct trec));
    if (!t)
	return NULL;
    t->rlink=r->rlink;
    t->linkid=h;
    t->tally=0;
    r->rlink=t;
    return t;
}
