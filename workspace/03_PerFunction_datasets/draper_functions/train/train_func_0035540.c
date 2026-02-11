brw_DO(struct brw_compile *p, unsigned execute_size)
{
   struct brw_context *brw = p->brw;

   if (brw->gen >= 6 || p->single_program_flow) {
      push_loop_stack(p, &p->store[p->nr_insn]);
      return &p->store[p->nr_insn];
   } else {
      struct brw_instruction *insn = next_insn(p, BRW_OPCODE_DO);

      push_loop_stack(p, insn);


      brw_set_dest(p, insn, brw_null_reg());
      brw_set_src0(p, insn, brw_null_reg());
      brw_set_src1(p, insn, brw_null_reg());

      insn->header.compression_control = BRW_COMPRESSION_NONE;
      insn->header.execution_size = execute_size;
      insn->header.predicate_control = BRW_PREDICATE_NONE;


      return insn;
   }
}
