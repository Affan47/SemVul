vce_v2_0_enable_mgcg(struct amdgpu_device *adev, bool enable)
{
	bool sw_cg = false;

	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_VCE_MGCG)) {
		if (sw_cg)
			vce_v2_0_set_sw_cg(adev, true);
		else
			vce_v2_0_set_dyn_cg(adev, true);
	} else {
		vce_v2_0_disable_cg(adev);

		if (sw_cg)
			vce_v2_0_set_sw_cg(adev, false);
		else
			vce_v2_0_set_dyn_cg(adev, false);
	}
}
