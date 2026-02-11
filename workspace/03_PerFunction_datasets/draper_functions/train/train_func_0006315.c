fiji_dpm_init_microcode(struct amdgpu_device *adev)
{
	char fw_name[30] = "amdgpu/fiji_smc.bin";
	int err;

	err = request_firmware(&adev->pm.fw, fw_name, adev->dev);
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->pm.fw);

out:
	if (err) {
		DRM_ERROR("Failed to load firmware \"%s\"", fw_name);
		release_firmware(adev->pm.fw);
		adev->pm.fw = NULL;
	}
	return err;
}
