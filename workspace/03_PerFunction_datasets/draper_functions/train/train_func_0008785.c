talloc_destroy_pointer(void ***pptr)
{
	if ((uintptr_t)**pptr < getpagesize())
		TALLOC_ABORT("Double free or invalid talloc_set?");

	**pptr = (void *)1;
	return 0;
}
