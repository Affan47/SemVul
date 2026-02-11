dq_insert_tree(struct qtree_mem_dqinfo *info,
				 struct dquot *dquot)
{
	int tmp = QT_TREEOFF;

#ifdef __QUOTA_QT_PARANOIA
	if (info->dqi_blocks <= QT_TREEOFF) {
		quota_error(dquot->dq_sb, "Quota tree root isn't allocated!");
		return -EIO;
	}
#endif
	return do_insert_tree(info, dquot, &tmp, 0);
}
