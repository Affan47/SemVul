insn_encode_mod_rm(struct insn *self, uint64_t flags, uint8_t opc_ext)
{
	uint8_t mod_rm, mod, reg_opcode, rm;
	bool need_sib;

	need_sib	= insn_need_sib(self, flags);

	if (flags & INDEX) {
		mod	= 0x00;
	} else {
		if (flags & DIR_REVERSED)
			mod		= mod_dest_encode(flags);
		else
			mod		= mod_src_encode(flags);
	}

	if (flags & OPC_EXT) {
		reg_opcode		= opc_ext;
	} else {
		reg_opcode		= insn_encode_reg(self, flags);
	}

	if (need_sib)
		rm		= 0x04;
	else {
		rm		= insn_encode_rm(self, flags);
	}

	mod_rm		= x86_encode_mod_rm(mod, reg_opcode, rm);

	return mod_rm;
}
