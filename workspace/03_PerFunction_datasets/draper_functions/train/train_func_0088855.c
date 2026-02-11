qxl_surface_id_alloc(struct qxl_device *qdev,
		      struct qxl_bo *surf)
{
	uint32_t handle;
	int idr_ret;
	int count = 0;
again:
	idr_preload(GFP_ATOMIC);
	spin_lock(&qdev->surf_id_idr_lock);
	idr_ret = idr_alloc(&qdev->surf_id_idr, NULL, 1, 0, GFP_NOWAIT);
	spin_unlock(&qdev->surf_id_idr_lock);
	idr_preload_end();
	if (idr_ret < 0)
		return idr_ret;
	handle = idr_ret;

	if (handle >= qdev->rom->n_surfaces) {
		count++;
		spin_lock(&qdev->surf_id_idr_lock);
		idr_remove(&qdev->surf_id_idr, handle);
		spin_unlock(&qdev->surf_id_idr_lock);
		qxl_reap_surface_id(qdev, 2);
		goto again;
	}
	surf->surface_id = handle;

	spin_lock(&qdev->surf_id_idr_lock);
	qdev->last_alloced_surf_id = handle;
	spin_unlock(&qdev->surf_id_idr_lock);
	return 0;
}
