nilfs_mdt_restore_from_shadow_map(struct inode *inode)
{
	struct nilfs_mdt_info *mi = NILFS_MDT(inode);
	struct nilfs_inode_info *ii = NILFS_I(inode);
	struct nilfs_shadow_map *shadow = mi->mi_shadow;

	down_write(&mi->mi_sem);

	if (mi->mi_palloc_cache)
		nilfs_palloc_clear_cache(inode);

	nilfs_clear_dirty_pages(inode->i_mapping, true);
	nilfs_copy_back_pages(inode->i_mapping, &shadow->frozen_data);

	nilfs_clear_dirty_pages(&ii->i_btnode_cache, true);
	nilfs_copy_back_pages(&ii->i_btnode_cache, &shadow->frozen_btnodes);

	nilfs_bmap_restore(ii->i_bmap, &shadow->bmap_store);

	up_write(&mi->mi_sem);
}
