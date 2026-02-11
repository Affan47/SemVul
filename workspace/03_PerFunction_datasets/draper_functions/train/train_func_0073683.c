gru_send_message_gpa(struct gru_message_queue_desc *mqd, void *mesg,
				unsigned int bytes)
{
	struct message_header *mhdr;
	void *cb;
	void *dsr;
	int istatus, clines, ret;

	STAT(mesq_send);
	BUG_ON(bytes < sizeof(int) || bytes > 2 * GRU_CACHE_LINE_BYTES);

	clines = DIV_ROUND_UP(bytes, GRU_CACHE_LINE_BYTES);
	if (gru_get_cpu_resources(bytes, &cb, &dsr))
		return MQE_BUG_NO_RESOURCES;
	memcpy(dsr, mesg, bytes);
	mhdr = dsr;
	mhdr->present = MQS_FULL;
	mhdr->lines = clines;
	if (clines == 2) {
		mhdr->present2 = get_present2(mhdr);
		restore_present2(mhdr, MQS_FULL);
	}

	do {
		ret = MQE_OK;
		gru_mesq(cb, mqd->mq_gpa, gru_get_tri(mhdr), clines, IMA);
		istatus = gru_wait(cb);
		if (istatus != CBS_IDLE)
			ret = send_message_failure(cb, mqd, dsr, clines);
	} while (ret == MQIE_AGAIN);
	gru_free_cpu_resources(cb, dsr);

	if (ret)
		STAT(mesq_send_failed);
	return ret;
}
