analysergetlocationcount(Location *addr, int *c)
{
	if (addr) {
		analysergetlocationcount(addr->left, c);
		if (!(addr->flags & AF_DELETED)) (*c)++;
		analysergetlocationcount(addr->right, c);
	}
}
