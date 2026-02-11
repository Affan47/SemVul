pci_create_attr(struct pci_dev *pdev, int num, int write_combine)
{

	int name_len = write_combine ? 13 : 10;
	struct bin_attribute *res_attr;
	int retval;

	res_attr = kzalloc(sizeof(*res_attr) + name_len, GFP_ATOMIC);
	if (res_attr) {
		char *res_attr_name = (char *)(res_attr + 1);

		sysfs_bin_attr_init(res_attr);
		if (write_combine) {
			pdev->res_attr_wc[num] = res_attr;
			sprintf(res_attr_name, "resource%d_wc", num);
			res_attr->mmap = pci_mmap_resource_wc;
		} else {
			pdev->res_attr[num] = res_attr;
			sprintf(res_attr_name, "resource%d", num);
			res_attr->mmap = pci_mmap_resource_uc;
		}
		if (pci_resource_flags(pdev, num) & IORESOURCE_IO) {
			res_attr->read = pci_read_resource_io;
			res_attr->write = pci_write_resource_io;
		}
		res_attr->attr.name = res_attr_name;
		res_attr->attr.mode = S_IRUSR | S_IWUSR;
		res_attr->size = pci_resource_len(pdev, num);
		res_attr->private = &pdev->resource[num];
		retval = sysfs_create_bin_file(&pdev->dev.kobj, res_attr);
	} else
		retval = -ENOMEM;

	return retval;
}
