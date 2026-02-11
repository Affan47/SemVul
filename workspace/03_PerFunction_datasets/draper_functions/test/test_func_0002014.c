find_block(struct inode *inode, struct omfs_extent_entry *ent,
			sector_t block, int count, int *left)
{

	sector_t searched = 0;
	for (; count > 1; count--) {
		int numblocks = clus_to_blk(OMFS_SB(inode->i_sb),
			be64_to_cpu(ent->e_blocks));

		if (block >= searched  &&
		    block < searched + numblocks) {


			*left = numblocks - (block - searched);
			return clus_to_blk(OMFS_SB(inode->i_sb),
				be64_to_cpu(ent->e_cluster)) +
				block - searched;
		}
		searched += numblocks;
		ent++;
	}
	return 0;
}
