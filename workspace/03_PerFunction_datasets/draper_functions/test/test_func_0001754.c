hpi_dsp_code_close(struct dsp_code *dsp_code)
{
	HPI_DEBUG_LOG(DEBUG, "dsp code closed\n");
	release_firmware(dsp_code->pvt->firmware);
	kfree(dsp_code->pvt);
}
