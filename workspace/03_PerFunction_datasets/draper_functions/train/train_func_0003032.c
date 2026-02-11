constant_folding_mul(struct rc_instruction * inst)
{
	rc_swizzle swz = 0;
	unsigned int negate = 0;

	if (is_src_uniform_constant(inst->U.I.SrcReg[0], &swz, &negate)) {
		if (swz == RC_SWIZZLE_ONE) {
			inst->U.I.Opcode = RC_OPCODE_MOV;
			inst->U.I.SrcReg[0] = inst->U.I.SrcReg[1];
			if (negate)
				inst->U.I.SrcReg[0].Negate ^= RC_MASK_XYZW;
			return;
		} else if (swz == RC_SWIZZLE_ZERO) {
			inst->U.I.Opcode = RC_OPCODE_MOV;
			inst->U.I.SrcReg[0].Swizzle = RC_SWIZZLE_0000;
			return;
		}
	}

	if (is_src_uniform_constant(inst->U.I.SrcReg[1], &swz, &negate)) {
		if (swz == RC_SWIZZLE_ONE) {
			inst->U.I.Opcode = RC_OPCODE_MOV;
			if (negate)
				inst->U.I.SrcReg[0].Negate ^= RC_MASK_XYZW;
			return;
		} else if (swz == RC_SWIZZLE_ZERO) {
			inst->U.I.Opcode = RC_OPCODE_MOV;
			inst->U.I.SrcReg[0].Swizzle = RC_SWIZZLE_0000;
			return;
		}
	}
}
