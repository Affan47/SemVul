v9fs_test_inode_dotl(struct inode *inode, void *data)
{
	struct v9fs_inode *v9inode = V9FS_I(inode);
	struct p9_stat_dotl *st = (struct p9_stat_dotl *)data;


	if ((inode->i_mode & S_IFMT) != (st->st_mode & S_IFMT))
		return 0;

	if (inode->i_generation != st->st_gen)
		return 0;


	if (memcmp(&v9inode->qid.version,
		   &st->qid.version, sizeof(v9inode->qid.version)))
		return 0;

	if (v9inode->qid.type != st->qid.type)
		return 0;

	if (v9inode->qid.path != st->qid.path)
		return 0;
	return 1;
}
