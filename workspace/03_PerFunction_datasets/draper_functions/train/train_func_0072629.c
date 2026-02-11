qxl_debugfs_add_files(struct qxl_device *qdev,
			  struct drm_info_list *files,
			  unsigned nfiles)
{
	unsigned i;

	for (i = 0; i < qdev->debugfs_count; i++) {
		if (qdev->debugfs[i].files == files) {

			return 0;
		}
	}

	i = qdev->debugfs_count + 1;
	if (i > QXL_DEBUGFS_MAX_COMPONENTS) {
		DRM_ERROR("Reached maximum number of debugfs components.\n");
		DRM_ERROR("Report so we increase QXL_DEBUGFS_MAX_COMPONENTS.\n");
		return -EINVAL;
	}
	qdev->debugfs[qdev->debugfs_count].files = files;
	qdev->debugfs[qdev->debugfs_count].num_files = nfiles;
	qdev->debugfs_count = i;
#if defined(CONFIG_DEBUG_FS)
	drm_debugfs_create_files(files, nfiles,
				 qdev->ddev->control->debugfs_root,
				 qdev->ddev->control);
	drm_debugfs_create_files(files, nfiles,
				 qdev->ddev->primary->debugfs_root,
				 qdev->ddev->primary);
#endif
	return 0;
}
