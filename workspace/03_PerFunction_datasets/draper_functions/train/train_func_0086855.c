start_smic_transaction(struct si_sm_data *smic,
				  unsigned char *data, unsigned int size)
{
	unsigned int i;

	if (size < 2)
		return IPMI_REQ_LEN_INVALID_ERR;
	if (size > MAX_SMIC_WRITE_SIZE)
		return IPMI_REQ_LEN_EXCEEDED_ERR;

	if ((smic->state != SMIC_IDLE) && (smic->state != SMIC_HOSED))
		return IPMI_NOT_IN_MY_STATE_ERR;

	if (smic_debug & SMIC_DEBUG_MSG) {
		printk(KERN_DEBUG "start_smic_transaction -");
		for (i = 0; i < size; i++)
			printk(" %02x", (unsigned char) data[i]);
		printk("\n");
	}
	smic->error_retries = 0;
	memcpy(smic->write_data, data, size);
	smic->write_count = size;
	smic->orig_write_count = size;
	smic->write_pos = 0;
	smic->read_pos = 0;
	smic->state = SMIC_START_OP;
	smic->smic_timeout = SMIC_RETRY_TIMEOUT;
	return 0;
}
