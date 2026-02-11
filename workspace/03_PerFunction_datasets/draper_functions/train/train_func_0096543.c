pvdisplay_colons(const struct physical_volume *pv)
{
	char uuid[64] __attribute__((aligned(8)));

	if (!pv)
		return;

	if (!id_write_format(&pv->id, uuid, sizeof(uuid))) {
		stack;
		return;
	}

	log_print("%s:%s:%" PRIu64 ":-1:%" PRIu64 ":%" PRIu64 ":-1:%" PRIu32 ":%u:%u:%u:%s",
		  pv_dev_name(pv), pv->vg_name, pv->size,

		  pv->status,
		  pv->status & ALLOCATABLE_PV,

		  pv->pe_size / 2,
		  pv->pe_count,
		  pv->pe_count - pv->pe_alloc_count,
		  pv->pe_alloc_count, *uuid ? uuid : "none");
}
