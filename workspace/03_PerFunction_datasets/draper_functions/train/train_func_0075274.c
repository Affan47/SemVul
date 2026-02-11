ima_add_violation(struct file *file, const unsigned char *filename,
		       struct integrity_iint_cache *iint,
		       const char *op, const char *cause)
{
	struct ima_template_entry *entry;
	struct inode *inode = file_inode(file);
	struct ima_event_data event_data = {iint, file, filename, NULL, 0,
					    cause};
	int violation = 1;
	int result;


	atomic_long_inc(&ima_htable.violations);

	result = ima_alloc_init_template(&event_data, &entry);
	if (result < 0) {
		result = -ENOMEM;
		goto err_out;
	}
	result = ima_store_template(entry, violation, inode, filename);
	if (result < 0)
		ima_free_template_entry(entry);
err_out:
	integrity_audit_msg(AUDIT_INTEGRITY_PCR, inode, filename,
			    op, cause, result, 0);
}
