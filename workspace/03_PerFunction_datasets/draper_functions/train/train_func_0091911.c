radeon_driver_firstopen(struct drm_device *dev)
{
	int ret;
	drm_local_map_t *map;
	drm_radeon_private_t *dev_priv = dev->dev_private;

	dev_priv->gart_info.table_size = RADEON_PCIGART_TABLE_SIZE;

	dev_priv->fb_aper_offset = pci_resource_start(dev->pdev, 0);
	ret = drm_legacy_addmap(dev, dev_priv->fb_aper_offset,
				pci_resource_len(dev->pdev, 0),
				_DRM_FRAME_BUFFER, _DRM_WRITE_COMBINING, &map);
	if (ret != 0)
		return ret;

	return 0;
}
