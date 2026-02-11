mips64_emit_memop_fast64(mips64_jit_tcb_t *b,int write_op,
                                     int opcode,int base,int offset,
                                     int target,int keep_ll_bit,
                                     memop_fast_access op_handler)
{
   m_uint32_t val = sign_extend(offset,16);
   u_char *test1,*test2,*p_exit;

   test2 = NULL;


   mips64_load_imm(b,AMD64_RSI,val);
   amd64_alu_reg_membase(b->jit_ptr,X86_ADD,
                         AMD64_RSI,AMD64_R15,REG_OFFSET(base));


   amd64_mov_reg_reg_size(b->jit_ptr,X86_EBX,X86_ESI,4);
   amd64_shift_reg_imm_size(b->jit_ptr,X86_SHR,X86_EBX,MTS64_HASH_SHIFT,4);
   amd64_alu_reg_imm_size(b->jit_ptr,X86_AND,X86_EBX,MTS64_HASH_MASK,4);


   amd64_mov_reg_membase(b->jit_ptr,AMD64_RCX,
                         AMD64_R15,
                         OFFSET(cpu_mips_t,mts_u.mts64_cache),8);
   amd64_shift_reg_imm(b->jit_ptr,X86_SHL,AMD64_RBX,5);
   amd64_alu_reg_reg(b->jit_ptr,X86_ADD,AMD64_RCX,AMD64_RBX);


   amd64_mov_reg_reg(b->jit_ptr,AMD64_RAX,AMD64_RSI,8);
   amd64_alu_reg_imm(b->jit_ptr,X86_AND,AMD64_RAX,MIPS_MIN_PAGE_MASK);

   amd64_alu_reg_membase_size(b->jit_ptr,X86_CMP,AMD64_RAX,AMD64_RCX,
                              OFFSET(mts64_entry_t,gvpa),8);
   test1 = b->jit_ptr;
   x86_branch8(b->jit_ptr, X86_CC_NZ, 0, 1);


   if (write_op) {
      amd64_test_membase_imm_size(b->jit_ptr,
                                  AMD64_RCX,OFFSET(mts64_entry_t,flags),
                                  MTS_FLAG_COW,4);
      test2 = b->jit_ptr;
      amd64_branch8(b->jit_ptr, X86_CC_NZ, 0, 1);
   }


   amd64_alu_reg_imm(b->jit_ptr,X86_AND,X86_ESI,MIPS_MIN_PAGE_IMASK);
   amd64_mov_reg_membase(b->jit_ptr,AMD64_RBX,
                         AMD64_RCX,OFFSET(mts64_entry_t,hpa),8);


   op_handler(b,target);

   p_exit = b->jit_ptr;
   amd64_jump8(b->jit_ptr,0);
   if (test2)
      amd64_patch(test2,b->jit_ptr);


   amd64_patch(test1,b->jit_ptr);


   mips64_set_pc(b,b->start_pc+((b->mips_trans_pos-1)<<2));


   amd64_movsxd_reg_reg(b->jit_ptr,AMD64_RSI,X86_ESI);


   amd64_mov_reg_imm(b->jit_ptr,AMD64_RDX,target);


   amd64_mov_reg_reg(b->jit_ptr,AMD64_RDI,AMD64_R15,8);


   amd64_call_membase(b->jit_ptr,AMD64_R15,MEMOP_OFFSET(opcode));

   amd64_patch(p_exit,b->jit_ptr);
}
