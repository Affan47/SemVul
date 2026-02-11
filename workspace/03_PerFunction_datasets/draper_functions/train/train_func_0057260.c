scsi_init_procfs(void)
{
	struct proc_dir_entry *pde;

	proc_scsi = proc_mkdir("scsi", NULL);
	if (!proc_scsi)
		goto err1;

	pde = proc_create("scsi/scsi", 0, NULL, &proc_scsi_operations);
	if (!pde)
		goto err2;

	return 0;

err2:
	remove_proc_entry("scsi", NULL);
err1:
	return -ENOMEM;
}
