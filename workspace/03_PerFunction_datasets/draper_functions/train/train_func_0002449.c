vci_bitfield_iterate(struct lanai_dev *lanai,
	const unsigned long *lp,
	void (*func)(struct lanai_dev *,vci_t vci))
{
	vci_t vci;

	for_each_set_bit(vci, lp, NUM_VCI)
		func(lanai, vci);
}
