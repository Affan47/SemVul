outstream_close(struct hpi_message *phm, struct hpi_response *phr,
	void *h_owner)
{

	struct hpi_message hm;
	struct hpi_response hr;

	hpi_init_response(phr, HPI_OBJ_OSTREAM, HPI_OSTREAM_CLOSE, 0);

	hpios_msgxlock_lock(&msgx_lock);

	if (h_owner ==
		outstream_user_open[phm->adapter_index][phm->
			obj_index].h_owner) {


		outstream_user_open[phm->adapter_index][phm->
			obj_index].h_owner = NULL;
		hpios_msgxlock_unlock(&msgx_lock);

		hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
			HPI_OSTREAM_RESET);
		hm.adapter_index = phm->adapter_index;
		hm.obj_index = phm->obj_index;
		hw_entry_point(&hm, &hr);
		hpios_msgxlock_lock(&msgx_lock);
		if (hr.error) {
			outstream_user_open[phm->adapter_index][phm->
				obj_index].h_owner = h_owner;
			phr->error = hr.error;
		} else {
			outstream_user_open[phm->adapter_index][phm->
				obj_index].open_flag = 0;
			outstream_user_open[phm->adapter_index][phm->
				obj_index].h_owner = NULL;
		}
	} else {
		HPI_DEBUG_LOG(WARNING,
			"%p trying to close %d outstream %d owned by %p\n",
			h_owner, phm->adapter_index, phm->obj_index,
			outstream_user_open[phm->adapter_index][phm->
				obj_index].h_owner);
		phr->error = HPI_ERROR_OBJ_NOT_OPEN;
	}
	hpios_msgxlock_unlock(&msgx_lock);
}
