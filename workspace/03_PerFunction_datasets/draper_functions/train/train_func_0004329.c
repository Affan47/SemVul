brw_ENDIF(struct brw_compile *p)
{
   struct brw_context *brw = p->brw;
   struct brw_instruction *insn = NULL;
   struct brw_instruction *else_inst = NULL;
   struct brw_instruction *if_inst = NULL;
   struct brw_instruction *tmp;
   bool emit_endif = true;


   if (brw->gen < 6 && p->single_program_flow)
      emit_endif = false;


   if (emit_endif)
      insn = next_insn(p, BRW_OPCODE_ENDIF);


   p->if_depth_in_loop[p->loop_stack_depth]--;
   tmp = pop_if_stack(p);
   if (tmp->header.opcode == BRW_OPCODE_ELSE) {
      else_inst = tmp;
      tmp = pop_if_stack(p);
   }
   if_inst = tmp;

   if (!emit_endif) {

      convert_IF_ELSE_to_ADD(p, if_inst, else_inst);
      return;
   }

   if (brw->gen < 6) {
      brw_set_dest(p, insn, retype(brw_vec4_grf(0,0), BRW_REGISTER_TYPE_UD));
      brw_set_src0(p, insn, retype(brw_vec4_grf(0,0), BRW_REGISTER_TYPE_UD));
      brw_set_src1(p, insn, brw_imm_d(0x0));
   } else if (brw->gen == 6) {
      brw_set_dest(p, insn, brw_imm_w(0));
      brw_set_src0(p, insn, retype(brw_null_reg(), BRW_REGISTER_TYPE_D));
      brw_set_src1(p, insn, retype(brw_null_reg(), BRW_REGISTER_TYPE_D));
   } else {
      brw_set_dest(p, insn, retype(brw_null_reg(), BRW_REGISTER_TYPE_D));
      brw_set_src0(p, insn, retype(brw_null_reg(), BRW_REGISTER_TYPE_D));
      brw_set_src1(p, insn, brw_imm_ud(0));
   }

   insn->header.compression_control = BRW_COMPRESSION_NONE;
   insn->header.mask_control = BRW_MASK_ENABLE;
   insn->header.thread_control = BRW_THREAD_SWITCH;


   if (brw->gen < 6) {
      insn->bits3.if_else.jump_count = 0;
      insn->bits3.if_else.pop_count = 1;
      insn->bits3.if_else.pad0 = 0;
   } else if (brw->gen == 6) {
      insn->bits1.branch_gen6.jump_count = 2;
   } else {
      insn->bits3.break_cont.jip = 2;
   }
   patch_IF_ELSE(p, if_inst, else_inst, insn);
}
