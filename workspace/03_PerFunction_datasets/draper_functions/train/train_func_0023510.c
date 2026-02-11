extract_boe(uint32 insn, bool *invalid)
{
	uint32 value;

	value = (insn >> 21) & 0x1f;
	if (invalid != NULL && !valid_bo(value)) *invalid = true;
	return value & 0x1e;
}
