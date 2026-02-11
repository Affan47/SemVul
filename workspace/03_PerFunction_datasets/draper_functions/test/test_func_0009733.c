ibm_read_apci_table(struct file *filp, struct kobject *kobj,
				   struct bin_attribute *bin_attr,
				   char *buffer, loff_t pos, size_t size)
{
	int bytes_read = -EINVAL;
	char *table = NULL;

	pr_debug("%s: pos = %d, size = %zd\n", __func__, (int)pos, size);

	if (pos == 0) {
		bytes_read = ibm_get_table_from_acpi(&table);
		if (bytes_read > 0 && bytes_read <= size)
			memcpy(buffer, table, bytes_read);
		kfree(table);
	}
	return bytes_read;
}
