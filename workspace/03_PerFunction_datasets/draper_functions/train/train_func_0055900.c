extract_bdp(uint32 insn, bool *invalid)
{
	if (invalid) {
		if ((insn & (0x17 << 21)) != (0x07 << 21)
		&& (insn & (0x1d << 21)) != (0x19 << 21))
			*invalid = true;
	}
	return ((insn & 0xfffc) ^ 0x8000) - 0x8000;
}
