IFDHSetCapabilities(DWORD Lun, DWORD Tag,
	 DWORD Length,  PUCHAR Value)
{


	(void)Length;
	(void)Value;

	int reader_index;

	if (-1 == (reader_index = LunToReaderIndex(Lun)))
		return IFD_COMMUNICATION_ERROR;

	DEBUG_INFO4("tag: 0x" DWORD_X ", %s (lun: " DWORD_X ")", Tag,
		CcidSlots[reader_index].readerName, Lun);

	return IFD_NOT_SUPPORTED;
}
