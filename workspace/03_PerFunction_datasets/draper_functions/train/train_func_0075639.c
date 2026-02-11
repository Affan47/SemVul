istgt_lu_tape_build_sense_data(ISTGT_LU_TAPE *spec, uint8_t *data, int sk, int asc, int ascq)
{
	uint8_t *cp;
	int hlen = 0, len = 0, plen;
	int total;
	int data_len;

	data_len = istgt_lu_scsi_build_sense_data(data, sk, asc, ascq);
	hlen = 2;
	if (data_len < (hlen + 18)) {
		return data_len;
	}

	cp = &data[hlen + len];
	len = 8;


	if (spec != NULL && spec->eof) {
		BSET8(&cp[2], 7);
	}
	if (spec != NULL && spec->eom) {
		BSET8(&cp[2], 6);
	}


	cp[18] = 0;


	DSET16(&cp[19], 0);

	DSET32(&cp[21], 0);

	DSET32(&cp[25], 0);


	cp[29] = 0;
	plen = 30 - len;


	cp[7] = plen;

	total = hlen + len + plen;


	DSET16(&data[0], total - 2);

	return total;
}
