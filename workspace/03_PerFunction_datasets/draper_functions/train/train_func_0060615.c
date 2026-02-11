kRespondsTo(state_t *s, int funct_nr, int argc, reg_t *argv)
{
	reg_t obj = argv[0];
	int selector = KP_UINT(argv[1]);

	return make_reg(0, is_heap_object(s, obj)
			&& lookup_selector(s, obj, selector, NULL, NULL) != SELECTOR_NONE);
}
