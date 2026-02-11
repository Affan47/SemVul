blkfront_setup_discard(struct blkfront_info *info)
{
	int err;
	unsigned int discard_granularity;
	unsigned int discard_alignment;
	unsigned int discard_secure;

	info->feature_discard = 1;
	err = xenbus_gather(XBT_NIL, info->xbdev->otherend,
		"discard-granularity", "%u", &discard_granularity,
		"discard-alignment", "%u", &discard_alignment,
		NULL);
	if (!err) {
		info->discard_granularity = discard_granularity;
		info->discard_alignment = discard_alignment;
	}
	err = xenbus_gather(XBT_NIL, info->xbdev->otherend,
		    "discard-secure", "%d", &discard_secure,
		    NULL);
	if (!err)
		info->feature_secdiscard = !!discard_secure;
}
