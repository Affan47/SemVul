ceph_encode_dentry_release(void **p, struct dentry *dentry,
			       int mds, int drop, int unless)
{
	struct inode *dir = d_inode(dentry->d_parent);
	struct ceph_mds_request_release *rel = *p;
	struct ceph_dentry_info *di = ceph_dentry(dentry);
	int force = 0;
	int ret;


	spin_lock(&dentry->d_lock);
	if (di->lease_session && di->lease_session->s_mds == mds)
		force = 1;
	spin_unlock(&dentry->d_lock);

	ret = ceph_encode_inode_release(p, dir, mds, drop, unless, force);

	spin_lock(&dentry->d_lock);
	if (ret && di->lease_session && di->lease_session->s_mds == mds) {
		dout("encode_dentry_release %p mds%d seq %d\n",
		     dentry, mds, (int)di->lease_seq);
		rel->dname_len = cpu_to_le32(dentry->d_name.len);
		memcpy(*p, dentry->d_name.name, dentry->d_name.len);
		*p += dentry->d_name.len;
		rel->dname_seq = cpu_to_le32(di->lease_seq);
		__ceph_mdsc_drop_dentry_lease(dentry);
	}
	spin_unlock(&dentry->d_lock);
	return ret;
}
