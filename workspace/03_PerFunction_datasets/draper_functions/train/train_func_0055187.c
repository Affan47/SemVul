sci_request_by_tag(struct isci_host *ihost, u16 io_tag)
{
	u16 task_index;
	u16 task_sequence;

	task_index = ISCI_TAG_TCI(io_tag);

	if (task_index < ihost->task_context_entries) {
		struct isci_request *ireq = ihost->reqs[task_index];

		if (test_bit(IREQ_ACTIVE, &ireq->flags)) {
			task_sequence = ISCI_TAG_SEQ(io_tag);

			if (task_sequence == ihost->io_request_sequence[task_index])
				return ireq;
		}
	}

	return NULL;
}
