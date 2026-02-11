instream_message(struct hpi_message *phm,
	struct hpi_response *phr, void *h_owner)
{
	if (phm->obj_index >= aDAPTER_INFO[phm->adapter_index].num_instreams) {
		hpi_init_response(phr, HPI_OBJ_ISTREAM, phm->function,
			HPI_ERROR_INVALID_OBJ_INDEX);
		return;
	}

	switch (phm->function) {
	case HPI_ISTREAM_OPEN:
		instream_open(phm, phr, h_owner);
		break;
	case HPI_ISTREAM_CLOSE:
		instream_close(phm, phr, h_owner);
		break;
	default:
		hw_entry_point(phm, phr);
		break;
	}
}
