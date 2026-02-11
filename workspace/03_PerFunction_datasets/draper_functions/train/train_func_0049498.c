hsw_reset(struct sst_dsp *sst)
{

	sst_dsp_shim_update_bits_unlocked(sst, SST_CSR,
		SST_CSR_RST | SST_CSR_STALL,
		SST_CSR_RST | SST_CSR_STALL);


	mdelay(10);


	sst_dsp_shim_update_bits_unlocked(sst, SST_CSR,
		SST_CSR_RST | SST_CSR_STALL, SST_CSR_STALL);
}
