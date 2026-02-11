amdgpu_pp_print_status(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (adev->powerplay.ip_funcs->print_status)
		adev->powerplay.ip_funcs->print_status(
					adev->powerplay.pp_handle);
}
