fi_tigertree_check(fileinfo_t *fi)
{
	if (fi->tigertree.leaves) {
		unsigned depth;
		struct tth root;

		if (NULL == fi->tth) {
			g_warning("Trailer contains tigertree but no root hash");
			goto discard;
		}

		depth = tt_depth(fi->tigertree.num_leaves);

		if (
			fi->file_size_known &&
			fi->tigertree.num_leaves != tt_node_count_at_depth(fi->size, depth)
		) {
			g_warning("Trailer contains tigertree with invalid leaf count");
			goto discard;
		}

		STATIC_ASSERT(TTH_RAW_SIZE == sizeof(struct tth));
		root = tt_root_hash(fi->tigertree.leaves, fi->tigertree.num_leaves);
		if (!tth_eq(&root, fi->tth)) {
			g_warning("Trailer contains tigertree with non-matching root hash");
			goto discard;
		}
	}
	return;

discard:
	fi_tigertree_free(fi);
}
