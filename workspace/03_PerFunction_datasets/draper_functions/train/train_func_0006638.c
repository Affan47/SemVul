b43legacy_upload_initvals(struct b43legacy_wldev *dev)
{
	const size_t hdr_len = sizeof(struct b43legacy_fw_header);
	const struct b43legacy_fw_header *hdr;
	struct b43legacy_firmware *fw = &dev->fw;
	const struct b43legacy_iv *ivals;
	size_t count;
	int err;

	hdr = (const struct b43legacy_fw_header *)(fw->initvals->data);
	ivals = (const struct b43legacy_iv *)(fw->initvals->data + hdr_len);
	count = be32_to_cpu(hdr->size);
	err = b43legacy_write_initvals(dev, ivals, count,
				 fw->initvals->size - hdr_len);
	if (err)
		goto out;
	if (fw->initvals_band) {
		hdr = (const struct b43legacy_fw_header *)
		      (fw->initvals_band->data);
		ivals = (const struct b43legacy_iv *)(fw->initvals_band->data
			+ hdr_len);
		count = be32_to_cpu(hdr->size);
		err = b43legacy_write_initvals(dev, ivals, count,
					 fw->initvals_band->size - hdr_len);
		if (err)
			goto out;
	}
out:

	return err;
}
