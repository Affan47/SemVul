check_research_for_paste(struct treepath *path,
				     const struct cpu_key *key)
{
	struct item_head *found_ih = tp_item_head(path);

	if (is_direct_le_ih(found_ih)) {
		if (le_ih_k_offset(found_ih) +
		    op_bytes_number(found_ih,
				    get_last_bh(path)->b_size) !=
		    cpu_key_k_offset(key)
		    || op_bytes_number(found_ih,
				       get_last_bh(path)->b_size) !=
		    pos_in_item(path))
			reiserfs_panic(NULL, "PAP-5720", "found direct item "
				       "%h or position (%d) does not match "
				       "to key %K", found_ih,
				       pos_in_item(path), key);
	}
	if (is_indirect_le_ih(found_ih)) {
		if (le_ih_k_offset(found_ih) +
		    op_bytes_number(found_ih,
				    get_last_bh(path)->b_size) !=
		    cpu_key_k_offset(key)
		    || I_UNFM_NUM(found_ih) != pos_in_item(path)
		    || get_ih_free_space(found_ih) != 0)
			reiserfs_panic(NULL, "PAP-5730", "found indirect "
				       "item (%h) or position (%d) does not "
				       "match to key (%K)",
				       found_ih, pos_in_item(path), key);
	}
}
