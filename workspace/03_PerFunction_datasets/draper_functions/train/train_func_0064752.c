sgen_clear_tlabs (void)
{
	SgenThreadInfo *info;

	FOREACH_THREAD (info) {

		*info->tlab_start_addr = NULL;
		*info->tlab_next_addr = NULL;
		*info->tlab_temp_end_addr = NULL;
		*info->tlab_real_end_addr = NULL;
	} END_FOREACH_THREAD
}
