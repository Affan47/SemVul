hpi_instream_ancillary_get_info(u32 h_instream, u32 *pframe_space)
{
	struct hpi_message hm;
	struct hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_ANC_GET_INFO);
	if (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		return HPI_ERROR_INVALID_HANDLE;
	hpi_send_recv(&hm, &hr);
	if (pframe_space)
		*pframe_space =
			(hr.u.d.u.stream_info.buffer_size -
			hr.u.d.u.stream_info.data_available) /
			sizeof(struct hpi_anc_frame);
	return hr.error;
}
