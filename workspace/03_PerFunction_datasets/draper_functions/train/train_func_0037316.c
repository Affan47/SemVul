SyroVolcaSample_End(SyroHandle Handle)
{
	SyroManage *psm;

	psm = (SyroManage *)Handle;
	if (psm->Header != SYRO_MANAGE_HEADER) {
		return Status_InvalidHandle;
	}

	SyroVolcaSample_FreeCompressMemory(psm);

	free((uint8_t *)psm);

	return Status_Success;
}
