truncate_inode_pages_final(struct address_space *mapping)
{
	unsigned long nrshadows;
	unsigned long nrpages;


	mapping_set_exiting(mapping);


	nrpages = mapping->nrpages;
	smp_rmb();
	nrshadows = mapping->nrshadows;

	if (nrpages || nrshadows) {


		spin_lock_irq(&mapping->tree_lock);
		spin_unlock_irq(&mapping->tree_lock);

		truncate_inode_pages(mapping, 0);
	}
}
