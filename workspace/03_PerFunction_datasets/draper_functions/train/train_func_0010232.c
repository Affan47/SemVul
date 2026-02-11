xfs_cross_rename(
	struct xfs_trans	*tp,
	struct xfs_inode	*dp1,
	struct xfs_name		*name1,
	struct xfs_inode	*ip1,
	struct xfs_inode	*dp2,
	struct xfs_name		*name2,
	struct xfs_inode	*ip2,
	struct xfs_bmap_free	*free_list,
	xfs_fsblock_t		*first_block,
	int			spaceres)
{
	int		error = 0;
	int		ip1_flags = 0;
	int		ip2_flags = 0;
	int		dp2_flags = 0;


	error = xfs_dir_replace(tp, dp1, name1,
				ip2->i_ino,
				first_block, free_list, spaceres);
	if (error)
		goto out_trans_abort;


	error = xfs_dir_replace(tp, dp2, name2,
				ip1->i_ino,
				first_block, free_list, spaceres);
	if (error)
		goto out_trans_abort;


	if (dp1 != dp2) {
		dp2_flags = XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG;

		if (S_ISDIR(ip2->i_d.di_mode)) {
			error = xfs_dir_replace(tp, ip2, &xfs_name_dotdot,
						dp1->i_ino, first_block,
						free_list, spaceres);
			if (error)
				goto out_trans_abort;


			if (!S_ISDIR(ip1->i_d.di_mode)) {
				error = xfs_droplink(tp, dp2);
				if (error)
					goto out_trans_abort;
				error = xfs_bumplink(tp, dp1);
				if (error)
					goto out_trans_abort;
			}


			ip1_flags |= XFS_ICHGTIME_CHG;
			ip2_flags |= XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG;
		}

		if (S_ISDIR(ip1->i_d.di_mode)) {
			error = xfs_dir_replace(tp, ip1, &xfs_name_dotdot,
						dp2->i_ino, first_block,
						free_list, spaceres);
			if (error)
				goto out_trans_abort;


			if (!S_ISDIR(ip2->i_d.di_mode)) {
				error = xfs_droplink(tp, dp1);
				if (error)
					goto out_trans_abort;
				error = xfs_bumplink(tp, dp2);
				if (error)
					goto out_trans_abort;
			}


			ip1_flags |= XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG;
			ip2_flags |= XFS_ICHGTIME_CHG;
		}
	}

	if (ip1_flags) {
		xfs_trans_ichgtime(tp, ip1, ip1_flags);
		xfs_trans_log_inode(tp, ip1, XFS_ILOG_CORE);
	}
	if (ip2_flags) {
		xfs_trans_ichgtime(tp, ip2, ip2_flags);
		xfs_trans_log_inode(tp, ip2, XFS_ILOG_CORE);
	}
	if (dp2_flags) {
		xfs_trans_ichgtime(tp, dp2, dp2_flags);
		xfs_trans_log_inode(tp, dp2, XFS_ILOG_CORE);
	}
	xfs_trans_ichgtime(tp, dp1, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	xfs_trans_log_inode(tp, dp1, XFS_ILOG_CORE);
	return xfs_finish_rename(tp, free_list);

out_trans_abort:
	xfs_bmap_cancel(free_list);
	xfs_trans_cancel(tp);
	return error;
}
