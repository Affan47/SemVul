ext2_bmap(struct inode *inode, block_t block, size_t *nblocks)
{
    block_t ret;

    if (inode->flags & EXT4_EXTENTS_FLAG)
	ret = bmap_extent(inode, block, nblocks);
    else
	ret = bmap_traditional(inode, block, nblocks);

    return ret;
}
