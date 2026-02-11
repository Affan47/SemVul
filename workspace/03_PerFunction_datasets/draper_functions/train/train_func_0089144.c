gmc_v7_0_init_microcode(struct amdgpu_device *adev)
{
	const char *chip_name;
	char fw_name[30];
	int err;

	DRM_DEBUG("\n");

	switch (adev->asic_type) {
	case CHIP_BONAIRE:
		chip_name = "bonaire";
		break;
	case CHIP_HAWAII:
		chip_name = "hawaii";
		break;
	case CHIP_TOPAZ:
		chip_name = "topaz";
		break;
	case CHIP_KAVERI:
	case CHIP_KABINI:
	case CHIP_MULLINS:
		return 0;
	default: BUG();
	}

	if (adev->asic_type == CHIP_TOPAZ)
		snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_mc.bin", chip_name);
	else
		snprintf(fw_name, sizeof(fw_name), "radeon/%s_mc.bin", chip_name);

	err = request_firmware(&adev->mc.fw, fw_name, adev->dev);
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->mc.fw);

out:
	if (err) {
		printk(KERN_ERR
		       "cik_mc: Failed to load firmware \"%s\"\n",
		       fw_name);
		release_firmware(adev->mc.fw);
		adev->mc.fw = NULL;
	}
	return err;
}
