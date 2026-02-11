b43legacy_remove(struct ssb_device *dev)
{
	struct b43legacy_wl *wl = ssb_get_devtypedata(dev);
	struct b43legacy_wldev *wldev = ssb_get_drvdata(dev);


	cancel_work_sync(&wldev->restart_work);
	cancel_work_sync(&wl->firmware_load);
	complete(&wldev->fw_load_complete);

	B43legacy_WARN_ON(!wl);
	if (!wldev->fw.ucode)
		return;
	if (wl->current_dev == wldev)
		ieee80211_unregister_hw(wl->hw);

	b43legacy_one_core_detach(dev);

	if (list_empty(&wl->devlist))


		b43legacy_wireless_exit(dev, wl);
}
