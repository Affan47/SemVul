ceph_ioctl_set_layout(struct file *file, void __user *arg)
{
	struct inode *inode = file_inode(file);
	struct ceph_mds_client *mdsc = ceph_sb_to_client(inode->i_sb)->mdsc;
	struct ceph_mds_request *req;
	struct ceph_ioctl_layout l;
	struct ceph_inode_info *ci = ceph_inode(file_inode(file));
	struct ceph_ioctl_layout nl;
	int err;

	if (copy_from_user(&l, arg, sizeof(l)))
		return -EFAULT;


	err = ceph_do_getattr(file_inode(file), CEPH_STAT_CAP_LAYOUT, false);
	if (err)
		return err;

	memset(&nl, 0, sizeof(nl));
	if (l.stripe_count)
		nl.stripe_count = l.stripe_count;
	else
		nl.stripe_count = ceph_file_layout_stripe_count(ci->i_layout);
	if (l.stripe_unit)
		nl.stripe_unit = l.stripe_unit;
	else
		nl.stripe_unit = ceph_file_layout_su(ci->i_layout);
	if (l.object_size)
		nl.object_size = l.object_size;
	else
		nl.object_size = ceph_file_layout_object_size(ci->i_layout);
	if (l.data_pool)
		nl.data_pool = l.data_pool;
	else
		nl.data_pool = ceph_file_layout_pg_pool(ci->i_layout);


	nl.preferred_osd = le64_to_cpu(-1);

	err = __validate_layout(mdsc, &nl);
	if (err)
		return err;

	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_SETLAYOUT,
				       USE_AUTH_MDS);
	if (IS_ERR(req))
		return PTR_ERR(req);
	req->r_inode = inode;
	ihold(inode);
	req->r_num_caps = 1;

	req->r_inode_drop = CEPH_CAP_FILE_SHARED | CEPH_CAP_FILE_EXCL;

	req->r_args.setlayout.layout.fl_stripe_unit =
		cpu_to_le32(l.stripe_unit);
	req->r_args.setlayout.layout.fl_stripe_count =
		cpu_to_le32(l.stripe_count);
	req->r_args.setlayout.layout.fl_object_size =
		cpu_to_le32(l.object_size);
	req->r_args.setlayout.layout.fl_pg_pool = cpu_to_le32(l.data_pool);

	err = ceph_mdsc_do_request(mdsc, NULL, req);
	ceph_mdsc_put_request(req);
	return err;
}
