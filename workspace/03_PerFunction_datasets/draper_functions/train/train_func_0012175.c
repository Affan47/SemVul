isci_free_tag(struct isci_host *ihost, u16 io_tag)
{
	u16 tci = ISCI_TAG_TCI(io_tag);
	u16 seq = ISCI_TAG_SEQ(io_tag);


	if (isci_tci_active(ihost) == 0)
		return SCI_FAILURE_INVALID_IO_TAG;

	if (seq == ihost->io_request_sequence[tci]) {
		ihost->io_request_sequence[tci] = (seq+1) & (SCI_MAX_SEQ-1);

		isci_tci_free(ihost, tci);

		return SCI_SUCCESS;
	}
	return SCI_FAILURE_INVALID_IO_TAG;
}
