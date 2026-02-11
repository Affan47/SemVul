ceph_revalidate_work(struct work_struct *work)
{
	int issued;
	u32 orig_gen;
	struct ceph_inode_info *ci = container_of(work, struct ceph_inode_info,
						  i_revalidate_work);
	struct inode *inode = &ci->vfs_inode;

	spin_lock(&ci->i_ceph_lock);
	issued = __ceph_caps_issued(ci, NULL);
	orig_gen = ci->i_rdcache_gen;
	spin_unlock(&ci->i_ceph_lock);

	if (!(issued & CEPH_CAP_FILE_CACHE)) {
		dout("revalidate_work lost cache before validation %p\n",
		     inode);
		goto out;
	}

	if (!fscache_check_consistency(ci->fscache))
		fscache_invalidate(ci->fscache);

	spin_lock(&ci->i_ceph_lock);

	if (orig_gen > ci->i_fscache_gen) {
		ci->i_fscache_gen = orig_gen;
	}
	spin_unlock(&ci->i_ceph_lock);

out:
	iput(&ci->vfs_inode);
}
