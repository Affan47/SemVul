extract_bba(uint32 insn, bool *invalid)
{
	if (invalid != NULL && ((insn >> 16) & 0x1f) != ((insn >> 11) & 0x1f)) *invalid = 1;
	return 0;
}
