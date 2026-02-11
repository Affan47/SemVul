hpi_instream_read_buf(u32 h_instream, u8 *pb_data, u32 bytes_to_read)
{
	struct hpi_message hm;
	struct hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_READ);
	if (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		return HPI_ERROR_INVALID_HANDLE;
	hm.u.d.u.data.data_size = bytes_to_read;
	hm.u.d.u.data.pb_data = pb_data;

	hpi_send_recv(&hm, &hr);

	return hr.error;
}
