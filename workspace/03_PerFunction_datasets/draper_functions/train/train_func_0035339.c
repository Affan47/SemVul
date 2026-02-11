_rbd_dev_v2_snap_features(struct rbd_device *rbd_dev, u64 snap_id,
		u64 *snap_features)
{
	__le64 snapid = cpu_to_le64(snap_id);
	struct {
		__le64 features;
		__le64 incompat;
	} __attribute__ ((packed)) features_buf = { 0 };
	u64 incompat;
	int ret;

	ret = rbd_obj_method_sync(rbd_dev, rbd_dev->header_name,
				"rbd", "get_features",
				&snapid, sizeof (snapid),
				&features_buf, sizeof (features_buf));
	dout("%s: rbd_obj_method_sync returned %d\n", __func__, ret);
	if (ret < 0)
		return ret;
	if (ret < sizeof (features_buf))
		return -ERANGE;

	incompat = le64_to_cpu(features_buf.incompat);
	if (incompat & ~RBD_FEATURES_SUPPORTED)
		return -ENXIO;

	*snap_features = le64_to_cpu(features_buf.features);

	dout("  snap_id 0x%016llx features = 0x%016llx incompat = 0x%016llx\n",
		(unsigned long long)snap_id,
		(unsigned long long)*snap_features,
		(unsigned long long)le64_to_cpu(features_buf.incompat));

	return 0;
}
