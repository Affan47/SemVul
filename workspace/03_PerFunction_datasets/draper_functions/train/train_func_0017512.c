add_lookupswitch_destinations(struct verifier_jump_destinations *jd, const unsigned char *code, unsigned long pc, unsigned long code_size)
{
	int npairs, def, err, offset;
	unsigned long base_pc, end_pc;

	base_pc = pc;
	pc += 1 + get_tableswitch_padding(pc);

	def = read_s32(code + pc);
	npairs = read_s32(code + pc + 4);
	pc += 8;

	err = valid_dest(def, base_pc, code_size);
	if (err)
		return err;

	err = add_jump_destination(jd, (unsigned long) base_pc + def);
	if (err)
		return err;

	end_pc = npairs * 4 * 2 + pc;
	pc += 4;

	while (pc < end_pc) {
		offset = read_s32(code + pc);

		err = valid_dest(offset, base_pc, code_size);
		if (err)
			return err;

		err = add_jump_destination(jd, (unsigned long) base_pc + offset);
		if (err)
			return err;

		pc += 8;
	}

	return 0;
}
