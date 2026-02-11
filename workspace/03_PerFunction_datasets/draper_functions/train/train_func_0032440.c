b43legacy_upload_beacon0(struct b43legacy_wldev *dev)
{
	struct b43legacy_wl *wl = dev->wl;

	if (wl->beacon0_uploaded)
		return;
	b43legacy_write_beacon_template(dev, 0x68, 0x18);


	b43legacy_write_probe_resp_template(dev, 0x268, 0x4A,
				      &__b43legacy_ratetable[3]);
	wl->beacon0_uploaded = true;
}
