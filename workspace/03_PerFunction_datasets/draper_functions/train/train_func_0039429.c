free_dns_res( struct proxy_l *p )
{
	if (p==NULL || p->dn==NULL)
		return;

	if (p->dn->kids)
		shm_free(p->dn->kids);
	shm_free(p->dn);
	p->dn = 0;
}
