res_to_dev_res(struct list_head *head,
					       struct resource *res)
{
	struct pci_dev_resource *dev_res;

	list_for_each_entry(dev_res, head, list) {
		if (dev_res->res == res) {
			int idx = res - &dev_res->dev->resource[0];

			dev_printk(KERN_DEBUG, &dev_res->dev->dev,
				 "res[%d]=%pR res_to_dev_res add_size %llx min_align %llx\n",
				 idx, dev_res->res,
				 (unsigned long long)dev_res->add_size,
				 (unsigned long long)dev_res->min_align);

			return dev_res;
		}
	}

	return NULL;
}
