hpi_adapter_get_mode(u16 adapter_index, u32 *padapter_mode)
{
	struct hpi_message hm;
	struct hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_GET_MODE);
	hm.adapter_index = adapter_index;
	hpi_send_recv(&hm, &hr);
	if (padapter_mode)
		*padapter_mode = hr.u.ax.mode.adapter_mode;
	return hr.error;
}
