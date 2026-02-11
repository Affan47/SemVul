print_ip(struct nes_cm_node *cm_node)
{
	unsigned char *rem_addr;
	if (cm_node) {
		rem_addr = (unsigned char *)&cm_node->rem_addr;
		printk(KERN_ERR PFX "Remote IP addr: %pI4\n", rem_addr);
	}
}
