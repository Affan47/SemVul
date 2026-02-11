extra_mon_dispatch(struct ceph_client *client, struct ceph_msg *msg)
{
	struct ceph_fs_client *fsc = client->private;
	int type = le16_to_cpu(msg->hdr.type);

	switch (type) {
	case CEPH_MSG_MDS_MAP:
		ceph_mdsc_handle_map(fsc->mdsc, msg);
		return 0;

	default:
		return -1;
	}
}
