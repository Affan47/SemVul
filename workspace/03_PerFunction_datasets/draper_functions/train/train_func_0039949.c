solos_pci_init(void)
{
	BUILD_BUG_ON(sizeof(struct solos_skb_cb) > sizeof(((struct sk_buff *)0)->cb));

	printk(KERN_INFO "Solos PCI Driver Version %s\n", VERSION);
	return pci_register_driver(&fpga_driver);
}
