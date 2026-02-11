alloc_net_table()
{
	if (net.allow)
		return true;
	net.allow = (unsigned int *) calloc(get_af_max(), sizeof(unsigned int));
	net.audit = (unsigned int *) calloc(get_af_max(), sizeof(unsigned int));
	net.deny = (unsigned int *) calloc(get_af_max(), sizeof(unsigned int));
	net.quiet = (unsigned int *) calloc(get_af_max(), sizeof(unsigned int));
	if (!net.allow || !net.audit || !net.deny || !net.quiet)
		return false;

	return true;
}
