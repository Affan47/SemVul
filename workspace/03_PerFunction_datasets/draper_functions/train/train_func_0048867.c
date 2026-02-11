cik_sdma_load_microcode(struct amdgpu_device *adev)
{
	const struct sdma_firmware_header_v1_0 *hdr;
	const __le32 *fw_data;
	u32 fw_size;
	int i, j;


	cik_sdma_enable(adev, false);

	for (i = 0; i < adev->sdma.num_instances; i++) {
		if (!adev->sdma.instance[i].fw)
			return -EINVAL;
		hdr = (const struct sdma_firmware_header_v1_0 *)adev->sdma.instance[i].fw->data;
		amdgpu_ucode_print_sdma_hdr(&hdr->header);
		fw_size = le32_to_cpu(hdr->header.ucode_size_bytes) / 4;
		adev->sdma.instance[i].fw_version = le32_to_cpu(hdr->header.ucode_version);
		adev->sdma.instance[i].feature_version = le32_to_cpu(hdr->ucode_feature_version);
		if (adev->sdma.instance[i].feature_version >= 20)
			adev->sdma.instance[i].burst_nop = true;
		fw_data = (const __le32 *)
			(adev->sdma.instance[i].fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
		WREG32(mmSDMA0_UCODE_ADDR + sdma_offsets[i], 0);
		for (j = 0; j < fw_size; j++)
			WREG32(mmSDMA0_UCODE_DATA + sdma_offsets[i], le32_to_cpup(fw_data++));
		WREG32(mmSDMA0_UCODE_ADDR + sdma_offsets[i], adev->sdma.instance[i].fw_version);
	}

	return 0;
}
