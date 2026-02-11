amdgpu_ucode_fini_bo(struct amdgpu_device *adev)
{
	int i;
	struct amdgpu_firmware_info *ucode = NULL;

	for (i = 0; i < AMDGPU_UCODE_ID_MAXIMUM; i++) {
		ucode = &adev->firmware.ucode[i];
		if (ucode->fw) {
			ucode->mc_addr = 0;
			ucode->kaddr = NULL;
		}
	}
	amdgpu_bo_unref(&adev->firmware.fw_buf);
	adev->firmware.fw_buf = NULL;

	return 0;
}
