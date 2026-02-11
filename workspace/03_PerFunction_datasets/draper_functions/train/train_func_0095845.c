calc_clu_hash(const char *name)
{
	unsigned  sum = 0;
	while  (*name)
		sum += *name++;
	return  sum % NETHASHMOD;
}
