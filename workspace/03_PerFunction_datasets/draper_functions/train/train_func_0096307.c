free_multi_body(struct multi_body * multi)
{
	struct part * p, *tmp;

	p = multi->first;


	while(p)
	{
		tmp =  p;
		p = p->next;
		pkg_free(tmp);
	}
	pkg_free(multi);
}
