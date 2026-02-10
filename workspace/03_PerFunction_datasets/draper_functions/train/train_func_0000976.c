cond_alloc(void)
{
    cond            *c;

    if (cond_free_list)
    {
        c = cond_free_list;
        cond_free_list = c->next;
    }
    else
        c = (cond *)mem_alloc(sizeof(cond));
    return c;
}
