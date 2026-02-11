refresh_pce(void *ignored)
{
	if (current->active_mm)
		load_mm_cr4(current->active_mm);
}
