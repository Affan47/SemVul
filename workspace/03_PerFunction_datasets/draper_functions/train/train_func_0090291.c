niu_try_msix(struct niu *np, u8 *ldg_num_map)
{
	struct msix_entry msi_vec[NIU_NUM_LDG];
	struct niu_parent *parent = np->parent;
	struct pci_dev *pdev = np->pdev;
	int i, num_irqs;
	u8 first_ldg;

	first_ldg = (NIU_NUM_LDG / parent->num_ports) * np->port;
	for (i = 0; i < (NIU_NUM_LDG / parent->num_ports); i++)
		ldg_num_map[i] = first_ldg + i;

	num_irqs = (parent->rxchan_per_port[np->port] +
		    parent->txchan_per_port[np->port] +
		    (np->port == 0 ? 3 : 1));
	BUG_ON(num_irqs > (NIU_NUM_LDG / parent->num_ports));

	for (i = 0; i < num_irqs; i++) {
		msi_vec[i].vector = 0;
		msi_vec[i].entry = i;
	}

	num_irqs = pci_enable_msix_range(pdev, msi_vec, 1, num_irqs);
	if (num_irqs < 0) {
		np->flags &= ~NIU_FLAGS_MSIX;
		return;
	}

	np->flags |= NIU_FLAGS_MSIX;
	for (i = 0; i < num_irqs; i++)
		np->ldg[i].irq = msi_vec[i].vector;
	np->num_ldg = num_irqs;
}
