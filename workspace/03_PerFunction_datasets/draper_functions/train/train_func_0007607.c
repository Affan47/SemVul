memory_init(void)
{
#ifdef CHECK_MASKS
	verify_masks();
#endif


	cur_context = -1;
	unmap_value = 0;


	if (!init_static())
		return 0;


	if (!init_cpudata())
		return 0;


	if (!verify_memory())
		return 0;
	if (!verify_ports())
		return 0;


	if (!allocate_memory())
		return 0;


	if (!populate_memory())
		return 0;
	if (!populate_ports())
		return 0;

	register_banks();

#ifdef MEM_DUMP

	mem_dump();
#endif

	return 1;
}
