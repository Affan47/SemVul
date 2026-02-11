ocrdma_query_gid(struct ib_device *ibdev, u8 port,
		     int index, union ib_gid *sgid)
{
	int ret;
	struct ocrdma_dev *dev;

	dev = get_ocrdma_dev(ibdev);
	memset(sgid, 0, sizeof(*sgid));
	if (index >= OCRDMA_MAX_SGID)
		return -EINVAL;

	ret = ib_get_cached_gid(ibdev, port, index, sgid, NULL);
	if (ret == -EAGAIN) {
		memcpy(sgid, &zgid, sizeof(*sgid));
		return 0;
	}

	return ret;
}
