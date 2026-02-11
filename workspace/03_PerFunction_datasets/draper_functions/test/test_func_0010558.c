recover_xattr_data(struct inode *inode, struct page *page, block_t blkaddr)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	nid_t prev_xnid = F2FS_I(inode)->i_xattr_nid;
	nid_t new_xnid = nid_of_node(page);
	struct node_info ni;


	if (!prev_xnid)
		goto recover_xnid;


	get_node_info(sbi, prev_xnid, &ni);
	f2fs_bug_on(sbi, ni.blk_addr == NULL_ADDR);
	invalidate_blocks(sbi, ni.blk_addr);
	dec_valid_node_count(sbi, inode);
	set_node_addr(sbi, &ni, NULL_ADDR, false);

recover_xnid:

	if (unlikely(!inc_valid_node_count(sbi, inode)))
		f2fs_bug_on(sbi, 1);

	remove_free_nid(NM_I(sbi), new_xnid);
	get_node_info(sbi, new_xnid, &ni);
	ni.ino = inode->i_ino;
	set_node_addr(sbi, &ni, NEW_ADDR, false);
	F2FS_I(inode)->i_xattr_nid = new_xnid;


	refresh_sit_entry(sbi, NEW_ADDR, blkaddr);
	set_node_addr(sbi, &ni, blkaddr, false);

	update_inode_page(inode);
}
