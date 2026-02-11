probe_ocfs(struct blkid_probe *probe,
		      struct blkid_magic *id __BLKID_ATTR((unused)),
		      unsigned char *buf)
{
	struct ocfs_volume_header ovh;
	struct ocfs_volume_label ovl;
	__u32 major;

	memcpy(&ovh, buf, sizeof(ovh));
	memcpy(&ovl, buf+512, sizeof(ovl));

	major = ocfsmajor(ovh);
	if (major == 1)
		blkid_set_tag(probe->dev,"SEC_TYPE","ocfs1",sizeof("ocfs1"));
	else if (major >= 9)
		blkid_set_tag(probe->dev,"SEC_TYPE","ntocfs",sizeof("ntocfs"));

	blkid_set_tag(probe->dev, "LABEL", ovl.label, ocfslabellen(ovl));
	blkid_set_tag(probe->dev, "MOUNT", ovh.mount, ocfsmountlen(ovh));
	set_uuid(probe->dev, ovl.vol_id, 0);
	return 0;
}
