quota_setxquota(struct super_block *sb, int type, qid_t id,
			   void __user *addr)
{
	struct fs_disk_quota fdq;
	struct qc_dqblk qdq;
	struct kqid qid;

	if (copy_from_user(&fdq, addr, sizeof(fdq)))
		return -EFAULT;
	if (!sb->s_qcop->set_dqblk)
		return -ENOSYS;
	qid = make_kqid(current_user_ns(), type, id);
	if (!qid_has_mapping(sb->s_user_ns, qid))
		return -EINVAL;

	if (from_kqid(sb->s_user_ns, qid) == 0 &&
	    fdq.d_fieldmask & (FS_DQ_WARNS_MASK | FS_DQ_TIMER_MASK)) {
		struct qc_info qinfo;
		int ret;

		if (!sb->s_qcop->set_info)
			return -EINVAL;
		copy_qcinfo_from_xfs_dqblk(&qinfo, &fdq);
		ret = sb->s_qcop->set_info(sb, type, &qinfo);
		if (ret)
			return ret;

		fdq.d_fieldmask &= ~(FS_DQ_WARNS_MASK | FS_DQ_TIMER_MASK);
	}
	copy_from_xfs_dqblk(&qdq, &fdq);
	return sb->s_qcop->set_dqblk(sb, qid, &qdq);
}
