brw_fb_WRITE(struct brw_compile *p,
		  int dispatch_width,
                  unsigned msg_reg_nr,
                  struct brw_reg src0,
                  unsigned msg_control,
                  unsigned binding_table_index,
                  unsigned msg_length,
                  unsigned response_length,
                  bool eot,
                  bool header_present)
{
   struct brw_context *brw = p->brw;
   struct brw_instruction *insn;
   unsigned msg_type;
   struct brw_reg dest;

   if (dispatch_width == 16)
      dest = retype(vec16(brw_null_reg()), BRW_REGISTER_TYPE_UW);
   else
      dest = retype(vec8(brw_null_reg()), BRW_REGISTER_TYPE_UW);

   if (brw->gen >= 6) {
      insn = next_insn(p, BRW_OPCODE_SENDC);
   } else {
      insn = next_insn(p, BRW_OPCODE_SEND);
   }

   insn->header.predicate_control = 0;
   insn->header.compression_control = BRW_COMPRESSION_NONE;

   if (brw->gen >= 6) {

      src0 = brw_message_reg(msg_reg_nr);

      msg_type = GEN6_DATAPORT_WRITE_MESSAGE_RENDER_TARGET_WRITE;
   } else {
      insn->header.destreg__conditionalmod = msg_reg_nr;

      msg_type = BRW_DATAPORT_WRITE_MESSAGE_RENDER_TARGET_WRITE;
   }

   brw_set_dest(p, insn, dest);
   brw_set_src0(p, insn, src0);
   brw_set_dp_write_message(p,
			    insn,
			    binding_table_index,
			    msg_control,
			    msg_type,
			    msg_length,
			    header_present,
			    eot,
			    response_length,
			    eot,
			    0 );
}
