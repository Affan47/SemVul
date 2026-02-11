__vxge_hw_vp_terminate(struct __vxge_hw_device *hldev, u32 vp_id)
{
	struct __vxge_hw_virtualpath *vpath;

	vpath = &hldev->virtual_paths[vp_id];

	if (vpath->vp_open == VXGE_HW_VP_NOT_OPEN)
		goto exit;

	VXGE_HW_DEVICE_TIM_INT_MASK_RESET(vpath->hldev->tim_int_mask0,
		vpath->hldev->tim_int_mask1, vpath->vp_id);
	hldev->stats.hw_dev_info_stats.vpath_info[vpath->vp_id] = NULL;


	spin_lock(&vpath->lock);
	vpath->vp_open = VXGE_HW_VP_NOT_OPEN;
	spin_unlock(&vpath->lock);

	vpath->vpmgmt_reg = NULL;
	vpath->nofl_db = NULL;
	vpath->max_mtu = 0;
	vpath->vsport_number = 0;
	vpath->max_kdfc_db = 0;
	vpath->max_nofl_db = 0;
	vpath->ringh = NULL;
	vpath->fifoh = NULL;
	memset(&vpath->vpath_handles, 0, sizeof(struct list_head));
	vpath->stats_block = NULL;
	vpath->hw_stats = NULL;
	vpath->hw_stats_sav = NULL;
	vpath->sw_stats = NULL;

exit:
	return;
}
