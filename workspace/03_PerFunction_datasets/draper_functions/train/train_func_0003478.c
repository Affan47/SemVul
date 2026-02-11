sci_stp_request_pio_data_in_copy_data(
	struct isci_stp_request *stp_req,
	u8 *data_buffer)
{
	enum sci_status status;


	if (stp_req->pio_len < SCU_MAX_FRAME_BUFFER_SIZE) {
		status = sci_stp_request_pio_data_in_copy_data_buffer(
			stp_req, data_buffer, stp_req->pio_len);

		if (status == SCI_SUCCESS)
			stp_req->pio_len = 0;
	} else {

		status = sci_stp_request_pio_data_in_copy_data_buffer(
			stp_req, data_buffer, SCU_MAX_FRAME_BUFFER_SIZE);

		if (status == SCI_SUCCESS)
			stp_req->pio_len -= SCU_MAX_FRAME_BUFFER_SIZE;
	}

	return status;
}
