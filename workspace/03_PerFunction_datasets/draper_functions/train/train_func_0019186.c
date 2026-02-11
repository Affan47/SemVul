ocfs2_metadata_cache_purge(struct ocfs2_caching_info *ci)
{
	unsigned int tree, to_purge, purged;
	struct rb_root root = RB_ROOT;

	BUG_ON(!ci || !ci->ci_ops);

	ocfs2_metadata_cache_lock(ci);
	tree = !(ci->ci_flags & OCFS2_CACHE_FL_INLINE);
	to_purge = ci->ci_num_cached;

	trace_ocfs2_metadata_cache_purge(
		(unsigned long long)ocfs2_metadata_cache_owner(ci),
		to_purge, tree);


	if (tree)
		root = ci->ci_cache.ci_tree;

	ocfs2_metadata_cache_reset(ci, 0);
	ocfs2_metadata_cache_unlock(ci);

	purged = ocfs2_purge_copied_metadata_tree(&root);


	if (tree && purged != to_purge)
		mlog(ML_ERROR, "Owner %llu, count = %u, purged = %u\n",
		     (unsigned long long)ocfs2_metadata_cache_owner(ci),
		     to_purge, purged);
}
