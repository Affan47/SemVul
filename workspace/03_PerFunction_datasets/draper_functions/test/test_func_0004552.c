brw_patch_break_cont(struct brw_compile *p, struct brw_instruction *while_inst)
{
   struct brw_context *brw = p->brw;
   struct brw_instruction *do_inst = get_inner_do_insn(p);
   struct brw_instruction *inst;
   int br = (brw->gen == 5) ? 2 : 1;

   for (inst = while_inst - 1; inst != do_inst; inst--) {


      if (inst->header.opcode == BRW_OPCODE_BREAK &&
	  inst->bits3.if_else.jump_count == 0) {
	 inst->bits3.if_else.jump_count = br * ((while_inst - inst) + 1);
      } else if (inst->header.opcode == BRW_OPCODE_CONTINUE &&
		 inst->bits3.if_else.jump_count == 0) {
	 inst->bits3.if_else.jump_count = br * (while_inst - inst);
      }
   }
}
