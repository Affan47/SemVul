remove_from_list(struct list_head *head,
				 struct resource *res)
{
	struct pci_dev_resource *dev_res, *tmp;

	list_for_each_entry_safe(dev_res, tmp, head, list) {
		if (dev_res->res == res) {
			list_del(&dev_res->list);
			kfree(dev_res);
			break;
		}
	}
}
