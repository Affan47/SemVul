ppc32_op_gen_page(cpu_ppc_t *cpu,ppc32_jit_tcb_t *b)
{
   struct ppc32_insn_tag *tag;
   cpu_gen_t *gcpu = cpu->gen;
   jit_op_t *iop;
   m_uint32_t cur_ia;
   u_char *jit_ptr;
   int i;


   for(b->ppc_trans_pos=0;
       b->ppc_trans_pos<PPC32_INSN_PER_PAGE;
       b->ppc_trans_pos++)
   {
      ppc32_op_emit_start(cpu,b);

      cur_ia = b->start_ia + (b->ppc_trans_pos << 2);

      if (ppc32_jit_tcb_get_target_bit(b,cur_ia))
         ppc32_op_emit_basic_opcode(cpu,JIT_OP_BRANCH_TARGET);

#if DEBUG_INSN_PERF_CNT
      ppc32_inc_perf_counter(cpu);
#endif
#if BREAKPOINT_ENABLE
      if (cpu->breakpoints_enabled)
         insn_emit_breakpoint(cpu,b);
#endif

      if (unlikely(!(tag = ppc32_jit_fetch_and_emit(cpu,b)))) {
         fprintf(stderr,"ppc32_op_gen_page: unable to fetch instruction.\n");
         return(-1);
      }
   }


   ppc32_op_emit_branch_target(cpu,b,b->start_ia);
   ppc32_op_emit_branch_target(cpu,b,cpu->ia);


   ppc32_op_optimize(gcpu,b);


   for(i=0;i<PPC32_INSN_PER_PAGE;i++)
   {
      jit_ptr = b->jit_ptr;


      ppc32_op_gen_list(b,i,gcpu->jit_op_array[i],jit_ptr);


      ppc32_jit_tcb_adjust_buffer(cpu,b);
   }


   for(i=0;i<PPC32_INSN_PER_PAGE;i++) {
      for(iop=gcpu->jit_op_array[i];iop;iop=iop->next)
         if (iop->opcode == JIT_OP_INSN_OUTPUT)
            ppc32_jit_tcb_apply_patches(cpu,b,iop);

      jit_op_free_list(gcpu,gcpu->jit_op_array[i]);
      gcpu->jit_op_array[i] = NULL;
   }


   ppc32_set_page_jump(cpu,b);


   ppc32_jit_tcb_free_patches(b);
   return(0);
}
