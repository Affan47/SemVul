scan_from_registered_roots (char *addr_start, char *addr_end, int root_type, ScanCopyContext ctx)
{
	void **start_root;
	RootRecord *root;
	SGEN_HASH_TABLE_FOREACH (&roots_hash [root_type], start_root, root) {
		SGEN_LOG (6, "Precise root scan %p-%p (desc: %p)", start_root, root->end_root, (void*)root->root_desc);
		precisely_scan_objects_from (start_root, (void**)root->end_root, addr_start, addr_end, root->root_desc, ctx);
	} SGEN_HASH_TABLE_FOREACH_END;
}
