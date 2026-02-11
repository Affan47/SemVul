cliprdr_process_format_data_response_event(cliprdrPlugin* cliprdr, FRDP_CB_DATA_RESPONSE_EVENT* cb_event)
{
	STREAM* data_out;

	data_out = cliprdr_packet_new(CB_FORMAT_DATA_RESPONSE, CB_RESPONSE_OK, cb_event->size);
	stream_write(data_out, cb_event->data, cb_event->size);
	cliprdr_packet_send(cliprdr, data_out);
}
