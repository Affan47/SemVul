mono_gc_deregister_root (char* addr)
{
	int root_type;
	RootRecord root;

	LOCK_GC;
	for (root_type = 0; root_type < ROOT_TYPE_NUM; ++root_type) {
		if (sgen_hash_table_remove (&roots_hash [root_type], addr, &root))
			roots_size -= (root.end_root - addr);
	}
	UNLOCK_GC;
}
