radeonTransformDeriv(struct radeon_compiler* c,
	struct rc_instruction* inst,
	void* unused)
{
	if (inst->U.I.Opcode != RC_OPCODE_DDX && inst->U.I.Opcode != RC_OPCODE_DDY)
		return 0;

	inst->U.I.SrcReg[1].Swizzle = RC_SWIZZLE_1111;
	inst->U.I.SrcReg[1].Negate = RC_MASK_XYZW;

	return 1;
}
