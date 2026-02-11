fix_output_writes(struct emulate_branch_state * s, struct rc_instruction * inst)
{
	const struct rc_opcode_info * opcode;

	if (!s->BranchCount)
		return;

	opcode = rc_get_opcode_info(inst->U.I.Opcode);

	if (!opcode->HasDstReg)
		return;

	if (inst->U.I.DstReg.File == RC_FILE_OUTPUT) {
		struct remap_output_data remap;
		struct rc_instruction * inst_mov;

		remap.Output = inst->U.I.DstReg.Index;
		remap.Temporary = rc_find_free_temporary(s->C);

		for(struct rc_instruction * inst = s->C->Program.Instructions.Next;
		    inst != &s->C->Program.Instructions;
		    inst = inst->Next) {
			rc_remap_registers(inst, &remap_output_function, &remap);
		}

		inst_mov = rc_insert_new_instruction(s->C, s->C->Program.Instructions.Prev);
		inst_mov->U.I.Opcode = RC_OPCODE_MOV;
		inst_mov->U.I.DstReg.File = RC_FILE_OUTPUT;
		inst_mov->U.I.DstReg.Index = remap.Output;
		inst_mov->U.I.DstReg.WriteMask = RC_MASK_XYZW;
		inst_mov->U.I.SrcReg[0].File = RC_FILE_TEMPORARY;
		inst_mov->U.I.SrcReg[0].Index = remap.Temporary;
	}
}
