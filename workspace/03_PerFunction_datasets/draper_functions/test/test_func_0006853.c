amdgpu_pp_set_clockgating_state(void *handle,
					enum amd_clockgating_state state)
{
	int ret = 0;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (adev->powerplay.ip_funcs->set_clockgating_state)
		ret = adev->powerplay.ip_funcs->set_clockgating_state(
				adev->powerplay.pp_handle, state);
	return ret;
}
