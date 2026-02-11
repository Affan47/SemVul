c_gc_normalise(state_t *s)
{
	reg_t addr = cmd_params[0].reg;

	GET_SEG_INTERFACE(addr.segment);

	addr = seg_interface->find_canonic_address(seg_interface, addr);
	sciprintf(" "PREG"\n", PRINT_REG(addr));

	seg_interface->deallocate_self(seg_interface);
	return 0;

}
