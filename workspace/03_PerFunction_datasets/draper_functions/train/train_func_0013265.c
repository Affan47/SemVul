outstream_write(struct hpi_adapter_obj *pao,
	struct hpi_message *phm, struct hpi_response *phr)
{
	struct hpi_hw_obj *phw = pao->priv;
	struct bus_master_interface *interface = phw->p_interface_buffer;
	struct hpi_hostbuffer_status *status;
	u32 space_available;

	if (!phw->outstream_host_buffer_size[phm->obj_index]) {

		hw_message(pao, phm, phr);
		return;
	}

	hpi_init_response(phr, phm->object, phm->function, 0);
	status = &interface->outstream_host_buffer_status[phm->obj_index];

	space_available = outstream_get_space_available(status);
	if (space_available < phm->u.d.u.data.data_size) {
		phr->error = HPI_ERROR_INVALID_DATASIZE;
		return;
	}


	if (phm->u.d.u.data.pb_data
		&& hpios_locked_mem_valid(&phw->outstream_host_buffers[phm->
				obj_index])) {
		u8 *p_bbm_data;
		u32 l_first_write;
		u8 *p_app_data = (u8 *)phm->u.d.u.data.pb_data;

		if (hpios_locked_mem_get_virt_addr(&phw->
				outstream_host_buffers[phm->obj_index],
				(void *)&p_bbm_data)) {
			phr->error = HPI_ERROR_INVALID_OPERATION;
			return;
		}


		l_first_write =
			min(phm->u.d.u.data.data_size,
			status->size_in_bytes -
			(status->host_index & (status->size_in_bytes - 1)));

		memcpy(p_bbm_data +
			(status->host_index & (status->size_in_bytes - 1)),
			p_app_data, l_first_write);

		memcpy(p_bbm_data, p_app_data + l_first_write,
			phm->u.d.u.data.data_size - l_first_write);
	}


	if (phw->flag_outstream_just_reset[phm->obj_index]) {

		u16 function = phm->function;
		phw->flag_outstream_just_reset[phm->obj_index] = 0;
		phm->function = HPI_OSTREAM_SET_FORMAT;
		hw_message(pao, phm, phr);
		phm->function = function;
		if (phr->error)
			return;
	}

	status->host_index += phm->u.d.u.data.data_size;
}
