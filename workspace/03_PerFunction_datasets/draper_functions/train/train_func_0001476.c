exec_page_free(cpu_mips_t *cpu,insn_exec_page_t *p)
{
   if (p) {
      p->next = cpu->exec_page_free_list;
      cpu->exec_page_free_list = p;
      cpu->exec_page_alloc--;
   }
}
