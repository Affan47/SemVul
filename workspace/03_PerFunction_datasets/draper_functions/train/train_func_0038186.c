hw_message(struct hpi_adapter_obj *pao, struct hpi_message *phm,
	struct hpi_response *phr)
{

	u16 err = 0;

	hpios_dsplock_lock(pao);

	err = message_response_sequence(pao, phm, phr);


	if (err) {

		if (err >= HPI_ERROR_BACKEND_BASE) {
			phr->error = HPI_ERROR_DSP_COMMUNICATION;
			phr->specific_error = err;
		} else {
			phr->error = err;
		}

		pao->dsp_crashed++;


		phr->size = sizeof(struct hpi_response_header);
		goto err;
	} else
		pao->dsp_crashed = 0;

	if (phr->error != 0)
		goto err;

	switch (phm->function) {
	case HPI_OSTREAM_WRITE:
	case HPI_ISTREAM_ANC_WRITE:
		err = hpi6205_transfer_data(pao, phm->u.d.u.data.pb_data,
			phm->u.d.u.data.data_size, H620_HIF_SEND_DATA);
		break;

	case HPI_ISTREAM_READ:
	case HPI_OSTREAM_ANC_READ:
		err = hpi6205_transfer_data(pao, phm->u.d.u.data.pb_data,
			phm->u.d.u.data.data_size, H620_HIF_GET_DATA);
		break;

	}
	phr->error = err;

err:
	hpios_dsplock_unlock(pao);

	return;
}
