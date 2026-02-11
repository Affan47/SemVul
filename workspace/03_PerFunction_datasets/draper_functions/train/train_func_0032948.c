parse_alloc_mptable_opt(char *p)
{
	enable_update_mptable = 1;
#ifdef CONFIG_PCI
	pci_routeirq = 1;
#endif
	alloc_mptable = 1;
	if (!p)
		return 0;
	mpc_new_length = memparse(p, &p);
	return 0;
}
