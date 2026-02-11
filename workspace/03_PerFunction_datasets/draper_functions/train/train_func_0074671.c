handle_cap_trunc(struct inode *inode,
			     struct ceph_mds_caps *trunc,
			     struct ceph_mds_session *session)
	__releases(ci->i_ceph_lock)
{
	struct ceph_inode_info *ci = ceph_inode(inode);
	int mds = session->s_mds;
	int seq = le32_to_cpu(trunc->seq);
	u32 truncate_seq = le32_to_cpu(trunc->truncate_seq);
	u64 truncate_size = le64_to_cpu(trunc->truncate_size);
	u64 size = le64_to_cpu(trunc->size);
	int implemented = 0;
	int dirty = __ceph_caps_dirty(ci);
	int issued = __ceph_caps_issued(ceph_inode(inode), &implemented);
	int queue_trunc = 0;

	issued |= implemented | dirty;

	dout("handle_cap_trunc inode %p mds%d seq %d to %lld seq %d\n",
	     inode, mds, seq, truncate_size, truncate_seq);
	queue_trunc = ceph_fill_file_size(inode, issued,
					  truncate_seq, truncate_size, size);
	spin_unlock(&ci->i_ceph_lock);

	if (queue_trunc) {
		ceph_queue_vmtruncate(inode);
		ceph_fscache_invalidate(inode);
	}
}
