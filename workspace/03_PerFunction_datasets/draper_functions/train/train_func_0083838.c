gsm1_receive(struct gsm_mux *gsm, unsigned char c)
{
	if (c == GSM1_SOF) {


		if (gsm->state == GSM_DATA && gsm->count) {

			gsm->count--;
			gsm->fcs = gsm_fcs_add(gsm->fcs, gsm->buf[gsm->count]);
			gsm->len = gsm->count;
			gsm_queue(gsm);
			gsm->state  = GSM_START;
			return;
		}

		if (gsm->state != GSM_START) {
			gsm->malformed++;
			gsm->state = GSM_START;
		}


		return;
	}

	if (c == GSM1_ESCAPE) {
		gsm->escape = 1;
		return;
	}


	if (gsm->state == GSM_SEARCH)
		return;

	if (gsm->escape) {
		c ^= GSM1_ESCAPE_BITS;
		gsm->escape = 0;
	}
	switch (gsm->state) {
	case GSM_START:
		gsm->address = 0;
		gsm->state = GSM_ADDRESS;
		gsm->fcs = INIT_FCS;

	case GSM_ADDRESS:
		gsm->fcs = gsm_fcs_add(gsm->fcs, c);
		if (gsm_read_ea(&gsm->address, c))
			gsm->state = GSM_CONTROL;
		break;
	case GSM_CONTROL:
		gsm->fcs = gsm_fcs_add(gsm->fcs, c);
		gsm->control = c;
		gsm->count = 0;
		gsm->state = GSM_DATA;
		break;
	case GSM_DATA:
		if (gsm->count > gsm->mru) {
			gsm->state = GSM_OVERRUN;
			gsm->bad_size++;
		} else
			gsm->buf[gsm->count++] = c;
		break;
	case GSM_OVERRUN:
		break;
	}
}
