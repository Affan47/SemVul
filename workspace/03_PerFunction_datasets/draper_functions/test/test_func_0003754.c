new_hashed_relocation(reiserfs_blocknr_hint_t * hint)
{
	char *hash_in;

	if (hint->formatted_node) {
		hash_in = (char *)&hint->key.k_dir_id;
	} else {
		if (!hint->inode) {

			hash_in = (char *)&hint->key.k_dir_id;
		} else
		    if (TEST_OPTION(displace_based_on_dirid, hint->th->t_super))
			hash_in = (char *)(&INODE_PKEY(hint->inode)->k_dir_id);
		else
			hash_in =
			    (char *)(&INODE_PKEY(hint->inode)->k_objectid);
	}

	hint->search_start =
	    hint->beg + keyed_hash(hash_in, 4) % (hint->end - hint->beg);
}
