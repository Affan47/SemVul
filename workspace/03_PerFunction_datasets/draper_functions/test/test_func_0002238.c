show_ext2_inode(const struct ext2_inode *inode)
{
	int i;

	print_sep(60);
	pr_bold_info("ext2 inode %p", inode);

	println("mode = 0x%05o", inode->mode);
	println("uid = %d", inode->uid);
	println("size = %d", inode->size);
	println("atime = %d", inode->atime);
	println("ctime = %d", inode->ctime);
	println("mtime = %d", inode->mtime);
	println("dtime = %d", inode->dtime);
	println("gid = %d", inode->gid);
	println("links_count = %d", inode->links_count);
	println("blocks = %d", inode->blocks);
	println("flags = 0x%08x", inode->flags);
	println("version = %d", inode->version);
	println("file_acl = %d", inode->file_acl);
	println("dir_acl = %d", inode->dir_acl);
	println("faddr = %d", inode->faddr);

	if ((inode->flags & EXT2_INODE_FLAG_EXTENTS) == 0)
	{
		for (i = 0; i < EXT2_N_BLOCKS; i++)
		{
			println("inode->block[%d] = %d", i, inode->block[i]);
		}
	}
}
