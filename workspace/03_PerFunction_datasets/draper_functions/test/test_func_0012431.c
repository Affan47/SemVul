xen_upload_processor_pm_data(void)
{
	struct acpi_processor *pr_backup = NULL;
	unsigned int i;
	int rc = 0;

	pr_info("Uploading Xen processor PM info\n");

	for_each_possible_cpu(i) {
		struct acpi_processor *_pr;
		_pr = per_cpu(processors, i );
		if (!_pr)
			continue;

		if (!pr_backup) {
			pr_backup = kzalloc(sizeof(struct acpi_processor), GFP_KERNEL);
			if (pr_backup)
				memcpy(pr_backup, _pr, sizeof(struct acpi_processor));
		}
		(void)upload_pm_data(_pr);
	}

	rc = check_acpi_ids(pr_backup);
	kfree(pr_backup);

	return rc;
}
