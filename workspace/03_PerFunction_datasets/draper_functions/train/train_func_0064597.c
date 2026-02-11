floppy_gen_floppydrive_select_set(void *s, unsigned int val)
{
	struct cpssp *cpssp = (struct cpssp *) s;

	if (DEBUG_CONTROL_FLOW) {
		fprintf(stderr, "%s: %u\n", __FUNCTION__, val);
	}

	cpssp->select = val;

	sig_boolean_or_set(cpssp->shugart_bus_trk0, cpssp,
			val & (cpssp->track == 0));
	sig_boolean_or_set(cpssp->shugart_bus_dskchg, cpssp,
			val & cpssp->changed);
	if (cpssp->select) {
		sig_shugart_bus_wp_set(cpssp->shugart_bus, cpssp, cpssp->wp);
	}
}
