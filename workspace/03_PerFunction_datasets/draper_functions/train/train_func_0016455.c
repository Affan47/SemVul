free_proxy(void)
{
    struct proxy *p = proxy_db;
    struct proxy *next_p;

    while (p)
    {
	regfree(&p->node_r);
	regfree(&p->remuser_r);
	next_p=p->next;
	free(p);
	p=next_p;
    }
    proxy_db = NULL;
}
