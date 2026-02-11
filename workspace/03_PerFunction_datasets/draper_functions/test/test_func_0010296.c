get_fw_version(struct kgd_dev *kgd, enum kgd_engine_type type)
{
	struct radeon_device *rdev = (struct radeon_device *) kgd;
	const union radeon_firmware_header *hdr;

	BUG_ON(kgd == NULL || rdev->mec_fw == NULL);

	switch (type) {
	case KGD_ENGINE_PFP:
		hdr = (const union radeon_firmware_header *) rdev->pfp_fw->data;
		break;

	case KGD_ENGINE_ME:
		hdr = (const union radeon_firmware_header *) rdev->me_fw->data;
		break;

	case KGD_ENGINE_CE:
		hdr = (const union radeon_firmware_header *) rdev->ce_fw->data;
		break;

	case KGD_ENGINE_MEC1:
		hdr = (const union radeon_firmware_header *) rdev->mec_fw->data;
		break;

	case KGD_ENGINE_MEC2:
		hdr = (const union radeon_firmware_header *)
							rdev->mec2_fw->data;
		break;

	case KGD_ENGINE_RLC:
		hdr = (const union radeon_firmware_header *) rdev->rlc_fw->data;
		break;

	case KGD_ENGINE_SDMA1:
	case KGD_ENGINE_SDMA2:
		hdr = (const union radeon_firmware_header *)
							rdev->sdma_fw->data;
		break;

	default:
		return 0;
	}

	if (hdr == NULL)
		return 0;


	return hdr->common.ucode_version;
}
