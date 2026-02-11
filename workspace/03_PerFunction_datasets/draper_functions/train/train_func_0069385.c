emit_arl(ir_instruction *ir,
        		        st_dst_reg dst, st_src_reg src0)
{
   int op = TGSI_OPCODE_ARL;

   if (src0.type == GLSL_TYPE_INT || src0.type == GLSL_TYPE_UINT)
      op = TGSI_OPCODE_UARL;

   assert(dst.file == PROGRAM_ADDRESS);
   if (dst.index >= this->num_address_regs)
      this->num_address_regs = dst.index + 1;

   emit(NULL, op, dst, src0);
}
