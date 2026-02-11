ceph_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct ceph_fs_client *fsc = ceph_inode_to_client(d_inode(dentry));
	struct ceph_monmap *monmap = fsc->client->monc.monmap;
	struct ceph_statfs st;
	u64 fsid;
	int err;

	dout("statfs\n");
	err = ceph_monc_do_statfs(&fsc->client->monc, &st);
	if (err < 0)
		return err;


	buf->f_type = CEPH_SUPER_MAGIC;


	buf->f_bsize = 1 << CEPH_BLOCK_SHIFT;
	buf->f_frsize = 1 << CEPH_BLOCK_SHIFT;
	buf->f_blocks = le64_to_cpu(st.kb) >> (CEPH_BLOCK_SHIFT-10);
	buf->f_bfree = le64_to_cpu(st.kb_avail) >> (CEPH_BLOCK_SHIFT-10);
	buf->f_bavail = le64_to_cpu(st.kb_avail) >> (CEPH_BLOCK_SHIFT-10);

	buf->f_files = le64_to_cpu(st.num_objects);
	buf->f_ffree = -1;
	buf->f_namelen = NAME_MAX;


	fsid = *(u64 *)(&monmap->fsid) ^ *((u64 *)&monmap->fsid + 1);
	buf->f_fsid.val[0] = fsid & 0xffffffff;
	buf->f_fsid.val[1] = fsid >> 32;

	return 0;
}
