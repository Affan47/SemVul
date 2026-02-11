sst_validate_fw_image(struct intel_sst_drv *ctx, unsigned long size,
		struct fw_module_header **module, u32 *num_modules)
{
	struct sst_fw_header *header;
	const void *sst_fw_in_mem = ctx->fw_in_mem;

	dev_dbg(ctx->dev, "Enter\n");


	header = (struct sst_fw_header *)sst_fw_in_mem;
	dev_dbg(ctx->dev,
		"header sign=%s size=%x modules=%x fmt=%x size=%zx\n",
		header->signature, header->file_size, header->modules,
		header->file_format, sizeof(*header));


	if ((strncmp(header->signature, SST_FW_SIGN, 4) != 0) ||
		(size != header->file_size + sizeof(*header))) {

		dev_err(ctx->dev, "InvalidFW sign/filesize mismatch\n");
		return -EINVAL;
	}
	*num_modules = header->modules;
	*module = (void *)sst_fw_in_mem + sizeof(*header);

	return 0;
}
