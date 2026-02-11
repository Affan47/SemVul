iscsi_queue_pdu(struct iscsi_context *iscsi, struct iscsi_pdu *pdu)
{
	if (iscsi == NULL) {
		printf("trying to queue to NULL context\n");
		return -1;
	}
	if (pdu == NULL) {
		printf("trying to queue NULL pdu\n");
		return -2;
	}
	DLIST_ADD_END(iscsi->outqueue, pdu, NULL);

	return 0;
}
