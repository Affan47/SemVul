ceph_set_super(struct super_block *s, void *data)
{
	struct ceph_fs_client *fsc = data;
	int ret;

	dout("set_super %p data %p\n", s, data);

	s->s_flags = fsc->mount_options->sb_flags;
	s->s_maxbytes = 1ULL << 40;

	s->s_xattr = ceph_xattr_handlers;
	s->s_fs_info = fsc;
	fsc->sb = s;

	s->s_op = &ceph_super_ops;
	s->s_export_op = &ceph_export_ops;

	s->s_time_gran = 1000;

	ret = set_anon_super(s, NULL);
	if (ret != 0)
		goto fail;

	return ret;

fail:
	s->s_fs_info = NULL;
	fsc->sb = NULL;
	return ret;
}
