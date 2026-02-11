cz_dpm_suspend(void *handle)
{
	int ret = 0;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (adev->pm.dpm_enabled) {
		mutex_lock(&adev->pm.mutex);

		ret = cz_dpm_disable(adev);

		adev->pm.dpm.current_ps =
			adev->pm.dpm.requested_ps =
			adev->pm.dpm.boot_ps;

		mutex_unlock(&adev->pm.mutex);
	}

	return ret;
}
