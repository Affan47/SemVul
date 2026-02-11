script_get_segment(state_t *s, int script_nr, int load)
{
	seg_id_t segment;

	if ((load & SCRIPT_GET_LOAD) == SCRIPT_GET_LOAD)
		script_instantiate(s, script_nr);

	segment = sm_seg_get(&s->seg_manager, script_nr);

	if (segment > 0) {
		if ((load & SCRIPT_GET_LOCK) == SCRIPT_GET_LOCK)
			sm_increment_lockers(&s->seg_manager, segment, SEG_ID);

		return segment;
	} else
		return 0;
}
