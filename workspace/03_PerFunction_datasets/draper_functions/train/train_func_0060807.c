probe_jfs(blkid_probe pr, const struct blkid_idmag *mag)
{
	struct jfs_super_block *js;

	js = blkid_probe_get_sb(pr, mag, struct jfs_super_block);
	if (!js)
		return errno ? -errno : 1;
	if (le32_to_cpu(js->js_bsize) != (1U << le16_to_cpu(js->js_l2bsize)))
		return 1;
	if (le32_to_cpu(js->js_pbsize) != (1U << le16_to_cpu(js->js_l2pbsize)))
		return 1;
	if ((le16_to_cpu(js->js_l2bsize) - le16_to_cpu(js->js_l2pbsize)) !=
	    le16_to_cpu(js->js_l2bfactor))
		return 1;

	if (strlen((char *) js->js_label))
		blkid_probe_set_label(pr, js->js_label, sizeof(js->js_label));
	blkid_probe_set_uuid(pr, js->js_uuid);
	return 0;
}
