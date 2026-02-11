brw_SAMPLE(struct brw_compile *p,
		struct brw_reg dest,
		unsigned msg_reg_nr,
		struct brw_reg src0,
		unsigned binding_table_index,
		unsigned sampler,
		unsigned msg_type,
		unsigned response_length,
		unsigned msg_length,
		unsigned header_present,
		unsigned simd_mode,
		unsigned return_format)
{
   struct brw_context *brw = p->brw;
   struct brw_instruction *insn;

   if (msg_reg_nr != -1)
      gen6_resolve_implied_move(p, &src0, msg_reg_nr);

   insn = next_insn(p, BRW_OPCODE_SEND);
   insn->header.predicate_control = 0;


   if (insn->header.compression_control != BRW_COMPRESSION_2NDHALF)
      insn->header.compression_control = BRW_COMPRESSION_NONE;

   if (brw->gen < 6)
      insn->header.destreg__conditionalmod = msg_reg_nr;

   brw_set_dest(p, insn, dest);
   brw_set_src0(p, insn, src0);
   brw_set_sampler_message(p, insn,
                           binding_table_index,
                           sampler,
                           msg_type,
                           response_length,
                           msg_length,
                           header_present,
                           simd_mode,
                           return_format);
}
