hpi_instream_host_buffer_allocate(u32 h_instream, u32 size_in_bytes)
{

	struct hpi_message hm;
	struct hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_HOSTBUFFER_ALLOC);
	if (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		return HPI_ERROR_INVALID_HANDLE;
	hm.u.d.u.data.data_size = size_in_bytes;
	hpi_send_recv(&hm, &hr);
	return hr.error;
}
