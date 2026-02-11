c_disasm(state_t *s)
{
	object_t *obj = obj_get(s, cmd_params[0].reg);
	int selector_id = script_find_selector(s, cmd_params[1].str);
	reg_t addr;

	if (!obj) {
		sciprintf("Not an object.");
		return 1;
	}

	if (selector_id < 0) {
		sciprintf("Not a valid selector name.");
		return 1;
	}

	if (lookup_selector(s, cmd_params[0].reg, selector_id, NULL, &addr) != SELECTOR_METHOD) {
		sciprintf("Not a method.");
		return 1;
	}

	do {
		addr = disassemble(s, addr, 0, 0);
	} while (addr.offset > 0);

	return 0;
}
