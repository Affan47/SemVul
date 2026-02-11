nilfs_mdt_save_to_shadow_map(struct inode *inode)
{
	struct nilfs_mdt_info *mi = NILFS_MDT(inode);
	struct nilfs_inode_info *ii = NILFS_I(inode);
	struct nilfs_shadow_map *shadow = mi->mi_shadow;
	int ret;

	ret = nilfs_copy_dirty_pages(&shadow->frozen_data, inode->i_mapping);
	if (ret)
		goto out;

	ret = nilfs_copy_dirty_pages(&shadow->frozen_btnodes,
				     &ii->i_btnode_cache);
	if (ret)
		goto out;

	nilfs_bmap_save(ii->i_bmap, &shadow->bmap_store);
 out:
	return ret;
}
