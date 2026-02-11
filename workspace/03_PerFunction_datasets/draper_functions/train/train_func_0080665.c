reiserfs_paste_into_item(struct reiserfs_transaction_handle *th,

			     struct treepath *search_path,

			     const struct cpu_key *key,

			     struct inode *inode,

			     const char *body,

			     int pasted_size)
{
	struct super_block *sb = inode->i_sb;
	struct tree_balance s_paste_balance;
	int retval;
	int fs_gen;
	int depth;

	BUG_ON(!th->t_trans_id);

	fs_gen = get_generation(inode->i_sb);

#ifdef REISERQUOTA_DEBUG
	reiserfs_debug(inode->i_sb, REISERFS_DEBUG_CODE,
		       "reiserquota paste_into_item(): allocating %u id=%u type=%c",
		       pasted_size, inode->i_uid,
		       key2type(&key->on_disk_key));
#endif

	depth = reiserfs_write_unlock_nested(sb);
	retval = dquot_alloc_space_nodirty(inode, pasted_size);
	reiserfs_write_lock_nested(sb, depth);
	if (retval) {
		pathrelse(search_path);
		return retval;
	}
	init_tb_struct(th, &s_paste_balance, th->t_super, search_path,
		       pasted_size);
#ifdef DISPLACE_NEW_PACKING_LOCALITIES
	s_paste_balance.key = key->on_disk_key;
#endif


	if (fs_changed(fs_gen, inode->i_sb)) {
		goto search_again;
	}

	while ((retval =
		fix_nodes(M_PASTE, &s_paste_balance, NULL,
			  body)) == REPEAT_SEARCH) {
search_again:

		PROC_INFO_INC(th->t_super, paste_into_item_restarted);
		retval =
		    search_for_position_by_key(th->t_super, key,
					       search_path);
		if (retval == IO_ERROR) {
			retval = -EIO;
			goto error_out;
		}
		if (retval == POSITION_FOUND) {
			reiserfs_warning(inode->i_sb, "PAP-5710",
					 "entry or pasted byte (%K) exists",
					 key);
			retval = -EEXIST;
			goto error_out;
		}
#ifdef CONFIG_REISERFS_CHECK
		check_research_for_paste(search_path, key);
#endif
	}


	if (retval == CARRY_ON) {
		do_balance(&s_paste_balance, NULL  , body, M_PASTE);
		return 0;
	}
	retval = (retval == NO_DISK_SPACE) ? -ENOSPC : -EIO;
error_out:

	unfix_nodes(&s_paste_balance);
#ifdef REISERQUOTA_DEBUG
	reiserfs_debug(inode->i_sb, REISERFS_DEBUG_CODE,
		       "reiserquota paste_into_item(): freeing %u id=%u type=%c",
		       pasted_size, inode->i_uid,
		       key2type(&key->on_disk_key));
#endif
	depth = reiserfs_write_unlock_nested(sb);
	dquot_free_space_nodirty(inode, pasted_size);
	reiserfs_write_lock_nested(sb, depth);
	return retval;
}
