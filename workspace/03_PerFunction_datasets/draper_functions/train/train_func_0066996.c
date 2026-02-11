mips64_try_direct_far_jump(cpu_mips_t *cpu,mips64_jit_tcb_t *b,
                                       m_uint64_t new_pc)
{
   m_uint64_t new_page;
   m_uint32_t pc_hash,pc_offset;
   u_char *test1,*test2,*test3;

   new_page = new_pc & MIPS_MIN_PAGE_MASK;
   pc_offset = (new_pc & MIPS_MIN_PAGE_IMASK) >> 2;
   pc_hash = mips64_jit_get_pc_hash(new_pc);


   amd64_mov_reg_membase(b->jit_ptr,AMD64_RBX,
                         AMD64_R15,OFFSET(cpu_mips_t,exec_blk_map),8);
   amd64_mov_reg_membase(b->jit_ptr,AMD64_RDX,
                         AMD64_RBX,pc_hash*sizeof(void *),8);


   amd64_test_reg_reg(b->jit_ptr,AMD64_RDX,AMD64_RDX);
   test1 = b->jit_ptr;
   amd64_branch8(b->jit_ptr, X86_CC_Z, 0, 1);


   mips64_load_imm(b,AMD64_RAX,new_page);
   amd64_alu_reg_membase_size(b->jit_ptr,X86_CMP,X86_EAX,AMD64_RDX,
                              OFFSET(mips64_jit_tcb_t,start_pc),4);
   test2 = b->jit_ptr;
   amd64_branch8(b->jit_ptr, X86_CC_NE, 0, 1);


   amd64_mov_reg_membase(b->jit_ptr,AMD64_RSI,
                         AMD64_RDX,OFFSET(mips64_jit_tcb_t,jit_insn_ptr),8);
   amd64_mov_reg_membase(b->jit_ptr,AMD64_RBX,
                         AMD64_RSI,pc_offset * sizeof(void *),8);

   amd64_test_reg_reg(b->jit_ptr,AMD64_RBX,AMD64_RBX);
   test3 = b->jit_ptr;
   amd64_branch8(b->jit_ptr, X86_CC_Z, 0, 1);
   amd64_jump_reg(b->jit_ptr,AMD64_RBX);


   amd64_patch(test1,b->jit_ptr);
   amd64_patch(test2,b->jit_ptr);
   amd64_patch(test3,b->jit_ptr);

   mips64_set_pc(b,new_pc);
   mips64_jit_tcb_push_epilog(b);
}
