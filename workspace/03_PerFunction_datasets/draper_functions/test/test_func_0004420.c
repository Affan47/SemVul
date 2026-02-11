bfad_debugfs_init(struct bfad_port_s *port)
{
	struct bfad_s *bfad = port->bfad;
	const struct bfad_debugfs_entry *file;
	char name[64];
	int i;

	if (!bfa_debugfs_enable)
		return;


	if (!bfa_debugfs_root) {
		bfa_debugfs_root = debugfs_create_dir("bfa", NULL);
		atomic_set(&bfa_debugfs_port_count, 0);
		if (!bfa_debugfs_root) {
			printk(KERN_WARNING
				"BFA debugfs root dir creation failed\n");
			goto err;
		}
	}


	snprintf(name, sizeof(name), "pci_dev:%s", bfad->pci_name);
	if (!port->port_debugfs_root) {
		port->port_debugfs_root =
			debugfs_create_dir(name, bfa_debugfs_root);
		if (!port->port_debugfs_root) {
			printk(KERN_WARNING
				"bfa %s: debugfs root creation failed\n",
				bfad->pci_name);
			goto err;
		}

		atomic_inc(&bfa_debugfs_port_count);

		for (i = 0; i < ARRAY_SIZE(bfad_debugfs_files); i++) {
			file = &bfad_debugfs_files[i];
			bfad->bfad_dentry_files[i] =
					debugfs_create_file(file->name,
							file->mode,
							port->port_debugfs_root,
							port,
							file->fops);
			if (!bfad->bfad_dentry_files[i]) {
				printk(KERN_WARNING
					"bfa %s: debugfs %s creation failed\n",
					bfad->pci_name, file->name);
				goto err;
			}
		}
	}

err:
	return;
}
