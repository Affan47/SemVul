c_gc_show_freeable(state_t *s)
{
	reg_t addr = cmd_params[0].reg;

	GET_SEG_INTERFACE(addr.segment);

	sciprintf("Freeable in segment %04x:\n", addr.segment);
	seg_interface->list_all_deallocatable(seg_interface, NULL, _print_address);

	seg_interface->deallocate_self(seg_interface);
	return 0;
}
