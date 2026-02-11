rc_for_all_reads_src(
	struct rc_instruction * inst,
	rc_read_src_fn cb,
	void * userdata)
{
	const struct rc_opcode_info * opcode =
					rc_get_opcode_info(inst->U.I.Opcode);


	if (inst->Type != RC_INSTRUCTION_NORMAL) {
		assert(0);
		return;
	}

	for(unsigned int src = 0; src < opcode->NumSrcRegs; ++src) {

		if (inst->U.I.SrcReg[src].File == RC_FILE_NONE)
			continue;

		if (inst->U.I.SrcReg[src].File == RC_FILE_PRESUB) {
			unsigned int i;
			unsigned int srcp_regs = rc_presubtract_src_reg_count(
						inst->U.I.PreSub.Opcode);
			for( i = 0; i < srcp_regs; i++) {
				cb(userdata, inst, &inst->U.I.PreSub.SrcReg[i]);
			}
		} else {
			cb(userdata, inst, &inst->U.I.SrcReg[src]);
		}
	}
}
