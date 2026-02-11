happy_meal_pci_exit(void)
{
	pci_unregister_driver(&hme_pci_driver);

	while (qfe_pci_list) {
		struct quattro *qfe = qfe_pci_list;
		struct quattro *next = qfe->next;

		kfree(qfe);

		qfe_pci_list = next;
	}
}
