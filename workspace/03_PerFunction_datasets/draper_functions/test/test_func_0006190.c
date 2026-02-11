mips64_emit_unknown(cpu_mips_t *cpu,mips64_jit_tcb_t *b,
                               mips_insn_t opcode)
{
   amd64_mov_reg_imm(b->jit_ptr,AMD64_RSI,opcode);
   amd64_mov_reg_reg(b->jit_ptr,AMD64_RDI,AMD64_R15,8);

   mips64_emit_c_call(b,mips64_unknown_opcode);
   return(0);
}
