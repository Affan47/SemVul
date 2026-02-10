beiscsi_module_init(void)
{
	int ret;

	beiscsi_scsi_transport =
			iscsi_register_transport(&beiscsi_iscsi_transport);
	if (!beiscsi_scsi_transport) {
		printk(KERN_ERR
		       "beiscsi_module_init - Unable to  register beiscsi transport.\n");
		return -ENOMEM;
	}
	printk(KERN_INFO "In beiscsi_module_init, tt=%p\n",
	       &beiscsi_iscsi_transport);

	ret = pci_register_driver(&beiscsi_pci_driver);
	if (ret) {
		printk(KERN_ERR
		       "beiscsi_module_init - Unable to  register beiscsi pci driver.\n");
		goto unregister_iscsi_transport;
	}
	return 0;

unregister_iscsi_transport:
	iscsi_unregister_transport(&beiscsi_iscsi_transport);
	return ret;
}
