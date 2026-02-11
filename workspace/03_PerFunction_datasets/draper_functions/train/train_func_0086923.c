sh_mmcif_read_block(struct sh_mmcif_host *host)
{
	struct device *dev = sh_mmcif_host_to_dev(host);
	struct mmc_data *data = host->mrq->data;
	u32 *p = sg_virt(data->sg);
	int i;

	if (host->sd_error) {
		data->error = sh_mmcif_error_manage(host);
		dev_dbg(dev, "%s(): %d\n", __func__, data->error);
		return false;
	}

	for (i = 0; i < host->blocksize / 4; i++)
		*p++ = sh_mmcif_readl(host->addr, MMCIF_CE_DATA);


	sh_mmcif_bitset(host, MMCIF_CE_INT_MASK, MASK_MBUFRE);
	host->wait_for = MMCIF_WAIT_FOR_READ_END;

	return true;
}
