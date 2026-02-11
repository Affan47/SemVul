HPIMSGX__init(struct hpi_message *phm,


	struct hpi_response *phr

	)
{
	hpi_handler_func *entry_point_func;
	struct hpi_response hr;


	hpi_init_response(&hr, phm->object, phm->function,
		HPI_ERROR_INVALID_OBJ);

	entry_point_func =
		hpi_lookup_entry_point_function(phm->u.s.resource.r.pci);

	if (entry_point_func) {
		HPI_DEBUG_MESSAGE(DEBUG, phm);
		entry_point_func(phm, &hr);
	} else {
		phr->error = HPI_ERROR_PROCESSING_MESSAGE;
		return phr->error;
	}
	if (hr.error == 0) {


		hpi_entry_points[hr.u.s.adapter_index] = entry_point_func;

		HPI_DEBUG_LOG(DEBUG,
			"HPI_SUBSYS_CREATE_ADAPTER successful,"
			" preparing adapter\n");
		adapter_prepare(hr.u.s.adapter_index);
	}
	memcpy(phr, &hr, hr.size);
	return phr->error;
}
