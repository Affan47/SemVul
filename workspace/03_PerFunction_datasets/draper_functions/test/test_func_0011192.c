manage_bandwidth(struct fw_card *card, int irm_id, int generation,
			    int bandwidth, bool allocate)
{
	int try, new, old = allocate ? BANDWIDTH_AVAILABLE_INITIAL : 0;
	__be32 data[2];


	for (try = 0; try < 5; try++) {
		new = allocate ? old - bandwidth : old + bandwidth;
		if (new < 0 || new > BANDWIDTH_AVAILABLE_INITIAL)
			return -EBUSY;

		data[0] = cpu_to_be32(old);
		data[1] = cpu_to_be32(new);
		switch (fw_run_transaction(card, TCODE_LOCK_COMPARE_SWAP,
				irm_id, generation, SCODE_100,
				CSR_REGISTER_BASE + CSR_BANDWIDTH_AVAILABLE,
				data, 8)) {
		case RCODE_GENERATION:

			return allocate ? -EAGAIN : bandwidth;

		case RCODE_COMPLETE:
			if (be32_to_cpup(data) == old)
				return bandwidth;

			old = be32_to_cpup(data);

		}
	}

	return -EIO;
}
