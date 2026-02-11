mei_hbm_version_is_supported(struct mei_device *dev)
{
	return	(dev->version.major_version < HBM_MAJOR_VERSION) ||
		(dev->version.major_version == HBM_MAJOR_VERSION &&
		 dev->version.minor_version <= HBM_MINOR_VERSION);
}
