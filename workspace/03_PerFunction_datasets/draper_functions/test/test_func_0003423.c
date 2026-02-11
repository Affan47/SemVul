sst_cache_and_parse_fw(struct intel_sst_drv *sst,
		const struct firmware *fw)
{
	int retval = 0;

	sst->fw_in_mem = kzalloc(fw->size, GFP_KERNEL);
	if (!sst->fw_in_mem) {
		retval = -ENOMEM;
		goto end_release;
	}
	dev_dbg(sst->dev, "copied fw to %p", sst->fw_in_mem);
	dev_dbg(sst->dev, "phys: %lx", (unsigned long)virt_to_phys(sst->fw_in_mem));
	memcpy(sst->fw_in_mem, fw->data, fw->size);
	retval = sst_parse_fw_memcpy(sst, fw->size, &sst->memcpy_list);
	if (retval) {
		dev_err(sst->dev, "Failed to parse fw\n");
		kfree(sst->fw_in_mem);
		sst->fw_in_mem = NULL;
	}

end_release:
	release_firmware(fw);
	return retval;

}
