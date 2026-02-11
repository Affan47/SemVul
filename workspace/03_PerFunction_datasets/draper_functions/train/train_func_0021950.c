print_arm_address(bfd_vma pc, struct disassemble_info *info, long given)
{
	void *stream = info->stream;
	fprintf_ftype func = info->fprintf_func;

	if (((given & 0x000f0000) == 0x000f0000)
	&& ((given & 0x02000000) == 0)) {
		int offset = given & 0xfff;

		func(stream, "[pc");

		if (given & 0x01000000) {
			if ((given & 0x00800000) == 0) offset = - offset;


			func(stream, ", #%d]", offset);

			offset += pc + 8;


			if (given & 0x00200000) func(stream, "!");
		} else {

			func(stream, "], #%d", offset);


			offset = pc + 8;
		}

		func(stream, "\t; ");
		info->print_address_func(offset, info);
	} else {
		func(stream, "[%s", arm_regnames[(given >> 16) & 0xf]);
		if ((given & 0x01000000) != 0) {
			if ((given & 0x02000000) == 0) {
				int offset = given & 0xfff;
				if (offset) {
					func(stream, ", #%s%d", (((given & 0x00800000) == 0) ? "-" : ""), offset);
				}
			} else {
				func(stream, ", %s", (((given & 0x00800000) == 0) ? "-" : ""));
				arm_decode_shift (given, func, stream);
			}
			func(stream, "]%s", ((given & 0x00200000) != 0) ? "!" : "");
		} else {
			if ((given & 0x02000000) == 0) {
				int offset = given & 0xfff;
				if (offset) {
					func(stream, "], #%s%d", (((given & 0x00800000) == 0) ? "-" : ""), offset);
				} else {
					func(stream, "]");
				}
			} else {
				func(stream, "], %s", (((given & 0x00800000) == 0) ? "-" : ""));
				arm_decode_shift (given, func, stream);
			}
		}
	}
}
