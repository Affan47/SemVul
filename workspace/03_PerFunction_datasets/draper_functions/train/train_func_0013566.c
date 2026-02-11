amdgpu_ucode_init_bo(struct amdgpu_device *adev)
{
	struct amdgpu_bo **bo = &adev->firmware.fw_buf;
	uint64_t fw_mc_addr;
	void *fw_buf_ptr = NULL;
	uint64_t fw_offset = 0;
	int i, err;
	struct amdgpu_firmware_info *ucode = NULL;
	const struct common_firmware_header *header = NULL;

	err = amdgpu_bo_create(adev, adev->firmware.fw_size, PAGE_SIZE, true,
			AMDGPU_GEM_DOMAIN_GTT, 0, NULL, NULL, bo);
	if (err) {
		dev_err(adev->dev, "(%d) Firmware buffer allocate failed\n", err);
		err = -ENOMEM;
		goto failed;
	}

	err = amdgpu_bo_reserve(*bo, false);
	if (err) {
		amdgpu_bo_unref(bo);
		dev_err(adev->dev, "(%d) Firmware buffer reserve failed\n", err);
		goto failed;
	}

	err = amdgpu_bo_pin(*bo, AMDGPU_GEM_DOMAIN_GTT, &fw_mc_addr);
	if (err) {
		amdgpu_bo_unreserve(*bo);
		amdgpu_bo_unref(bo);
		dev_err(adev->dev, "(%d) Firmware buffer pin failed\n", err);
		goto failed;
	}

	err = amdgpu_bo_kmap(*bo, &fw_buf_ptr);
	if (err) {
		dev_err(adev->dev, "(%d) Firmware buffer kmap failed\n", err);
		amdgpu_bo_unpin(*bo);
		amdgpu_bo_unreserve(*bo);
		amdgpu_bo_unref(bo);
		goto failed;
	}

	amdgpu_bo_unreserve(*bo);

	fw_offset = 0;
	for (i = 0; i < AMDGPU_UCODE_ID_MAXIMUM; i++) {
		ucode = &adev->firmware.ucode[i];
		if (ucode->fw) {
			header = (const struct common_firmware_header *)ucode->fw->data;
			amdgpu_ucode_init_single_fw(ucode, fw_mc_addr + fw_offset,
						    fw_buf_ptr + fw_offset);
			fw_offset += ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);
		}
	}

failed:
	if (err)
		adev->firmware.smu_load = false;

	return err;
}
