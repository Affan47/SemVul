gmc_v8_0_init_microcode(struct amdgpu_device *adev)
{
	const char *chip_name;
	char fw_name[30];
	int err;

	DRM_DEBUG("\n");

	switch (adev->asic_type) {
	case CHIP_TONGA:
		chip_name = "tonga";
		break;
	case CHIP_FIJI:
	case CHIP_CARRIZO:
	case CHIP_STONEY:
		return 0;
	default: BUG();
	}

	snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_mc.bin", chip_name);
	err = request_firmware(&adev->mc.fw, fw_name, adev->dev);
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->mc.fw);

out:
	if (err) {
		printk(KERN_ERR
		       "mc: Failed to load firmware \"%s\"\n",
		       fw_name);
		release_firmware(adev->mc.fw);
		adev->mc.fw = NULL;
	}
	return err;
}
