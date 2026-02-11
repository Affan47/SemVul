rc_print_normal_instruction(FILE * f, struct rc_instruction * inst, unsigned *branch_depth)
{
	const struct rc_opcode_info * opcode = rc_get_opcode_info(inst->U.I.Opcode);
	unsigned int reg;
	unsigned spaces = update_branch_depth(inst->U.I.Opcode, branch_depth);

	for (unsigned i = 0; i < spaces; i++)
		fprintf(f, " ");

	fprintf(f, "%s", opcode->Name);

	switch(inst->U.I.SaturateMode) {
	case RC_SATURATE_NONE: break;
	case RC_SATURATE_ZERO_ONE: fprintf(f, "_SAT"); break;
	case RC_SATURATE_MINUS_PLUS_ONE: fprintf(f, "_SAT2"); break;
	default: fprintf(f, "_BAD_SAT"); break;
	}

	if (opcode->HasDstReg) {
		fprintf(f, " ");
		rc_print_dst_register(f, inst->U.I.DstReg);
		print_omod_op(f, inst->U.I.Omod);
		if (opcode->NumSrcRegs)
			fprintf(f, ",");
	}

	for(reg = 0; reg < opcode->NumSrcRegs; ++reg) {
		if (reg > 0)
			fprintf(f, ",");
		fprintf(f, " ");
		rc_print_src_register(f, inst, inst->U.I.SrcReg[reg]);
	}

	if (opcode->HasTexture) {
		fprintf(f, ", %s%s[%u]%s%s",
			textarget_to_string(inst->U.I.TexSrcTarget),
			inst->U.I.TexShadow ? "SHADOW" : "",
			inst->U.I.TexSrcUnit,
			inst->U.I.TexSemWait ? " SEM_WAIT" : "",
			inst->U.I.TexSemAcquire ? " SEM_ACQUIRE" : "");
	}

	fprintf(f, ";");

	if (inst->U.I.WriteALUResult) {
		fprintf(f, " [aluresult = (");
		rc_print_comparefunc(f,
			(inst->U.I.WriteALUResult == RC_ALURESULT_X) ? "x" : "w",
			inst->U.I.ALUResultCompare, "0");
		fprintf(f, ")]");
	}

	if (inst->U.I.DstReg.Pred == RC_PRED_SET) {
		fprintf(f, " PRED_SET");
	} else if (inst->U.I.DstReg.Pred == RC_PRED_INV) {
		fprintf(f, " PRED_INV");
	}

	fprintf(f, "\n");
}
