insfree(struct list *l, struct block *b)
{
    struct block *nf;
    DXlock(&l->list_lock, 0);
    nf = l->block.next_free;
    b->next_free = nf;
    b->prev_free = &l->block;
    SETFREE(b);
    if (nf)
	nf->prev_free = b;
    l->block.next_free = b;
    DXunlock(&l->list_lock, 0);
}
