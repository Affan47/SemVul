analyse_ucode(int ucode_rev, uint8_t *data, uint32_t len)
{
	uint64_t *insns = (uint64_t*)data;
	struct insn insn;
	uint32_t i;

	for (i=0; i<len/sizeof(*insns); i++) {
		switch (ucode_rev) {
		case 1:
			disasm_ucode_1(insns[i], &insn);
			print_ucode_version(&insn);
			break;
		case 2:
			disasm_ucode_2(insns[i], &insn);
			print_ucode_version(&insn);
			break;
		case 3:
			disasm_ucode_3(insns[i], &insn);
			print_ucode_version(&insn);
			break;
		}
	}
}
