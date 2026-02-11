__vxge_hw_vp_terminate(struct __vxge_hw_device *hldev,
			struct __vxge_hw_virtualpath *vpath)
{
	vxge_trace();

	if (vpath->vp_open == VXGE_HW_VP_NOT_OPEN)
		return;

	VXGE_HW_DEVICE_TIM_INT_MASK_RESET(hldev->tim_int_mask0,
		hldev->tim_int_mask1, vpath->vp_id);

	memset(vpath, 0, sizeof(struct __vxge_hw_virtualpath));
}
