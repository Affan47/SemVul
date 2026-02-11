ptr_in_heap (char *object)
{
	if (sgen_ptr_in_nursery (object))
		return TRUE;

	if (sgen_los_is_valid_object (object))
		return TRUE;

	if (major_collector.is_valid_object (object))
		return TRUE;
	return FALSE;
}
