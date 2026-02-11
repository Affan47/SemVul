lower_brk(
	struct rc_instruction * inst,
	struct vert_fc_state * fc_state)
{
	if (fc_state->LoopDepth == 1) {
		inst->U.I.Opcode = RC_OPCODE_RCP;
		inst->U.I.DstReg.Pred = RC_PRED_INV;
		inst->U.I.SrcReg[0].Index = 0;
		inst->U.I.SrcReg[0].File = RC_FILE_NONE;
		inst->U.I.SrcReg[0].Swizzle = RC_SWIZZLE_0000;
	} else {
		inst->U.I.Opcode = RC_ME_PRED_SET_CLR;
		inst->U.I.DstReg.Pred = RC_PRED_SET;
	}

	build_pred_dst(&inst->U.I.DstReg, fc_state);
}
