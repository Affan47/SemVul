adf_ring_debugfs_add(struct adf_etr_ring_data *ring, const char *name)
{
	struct adf_etr_ring_debug_entry *ring_debug;
	char entry_name[8];

	ring_debug = kzalloc(sizeof(*ring_debug), GFP_KERNEL);
	if (!ring_debug)
		return -ENOMEM;

	strlcpy(ring_debug->ring_name, name, sizeof(ring_debug->ring_name));
	snprintf(entry_name, sizeof(entry_name), "ring_%02d",
		 ring->ring_number);

	ring_debug->debug = debugfs_create_file(entry_name, S_IRUSR,
						ring->bank->bank_debug_dir,
						ring, &adf_ring_debug_fops);
	if (!ring_debug->debug) {
		pr_err("QAT: Failed to create ring debug entry.\n");
		kfree(ring_debug);
		return -EFAULT;
	}
	ring->ring_debug = ring_debug;
	return 0;
}
