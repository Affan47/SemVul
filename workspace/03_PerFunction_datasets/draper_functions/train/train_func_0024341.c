cmp_addr(struct pppoe_addr *a, __be16 sid, char *addr)
{
	return a->sid == sid && ether_addr_equal(a->remote, addr);
}
