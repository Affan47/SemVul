sbp_run_transaction(struct fw_card *card, int tcode, int destination_id,
		int generation, int speed, unsigned long long offset,
		void *payload, size_t length)
{
	int attempt, ret, delay;

	for (attempt = 1; attempt <= 5; attempt++) {
		ret = fw_run_transaction(card, tcode, destination_id,
				generation, speed, offset, payload, length);

		switch (ret) {
		case RCODE_COMPLETE:
		case RCODE_TYPE_ERROR:
		case RCODE_ADDRESS_ERROR:
		case RCODE_GENERATION:
			return ret;

		default:
			delay = 5 * attempt * attempt;
			usleep_range(delay, delay * 2);
		}
	}

	return ret;
}
