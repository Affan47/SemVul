ceph_mdsc_lease_release(struct ceph_mds_client *mdsc, struct inode *inode,
			     struct dentry *dentry)
{
	struct ceph_dentry_info *di;
	struct ceph_mds_session *session;
	u32 seq;

	BUG_ON(inode == NULL);
	BUG_ON(dentry == NULL);


	spin_lock(&dentry->d_lock);
	di = ceph_dentry(dentry);
	if (!di || !di->lease_session ||
	    di->lease_session->s_mds < 0 ||
	    di->lease_gen != di->lease_session->s_cap_gen ||
	    !time_before(jiffies, dentry->d_time)) {
		dout("lease_release inode %p dentry %p -- "
		     "no lease\n",
		     inode, dentry);
		spin_unlock(&dentry->d_lock);
		return;
	}


	session = ceph_get_mds_session(di->lease_session);
	seq = di->lease_seq;
	__ceph_mdsc_drop_dentry_lease(dentry);
	spin_unlock(&dentry->d_lock);

	dout("lease_release inode %p dentry %p to mds%d\n",
	     inode, dentry, session->s_mds);
	ceph_mdsc_lease_send_msg(session, inode, dentry,
				 CEPH_MDS_LEASE_RELEASE, seq);
	ceph_put_mds_session(session);
}
