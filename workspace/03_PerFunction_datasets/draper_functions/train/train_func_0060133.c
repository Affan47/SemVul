ppc32_jit_init(cpu_ppc_t *cpu)
{
   insn_exec_page_t *cp;
   u_char *cp_addr;
   u_int area_size;
   size_t len;
   int i;


   len = PPC_JIT_IA_HASH_SIZE * sizeof(void *);
   cpu->exec_blk_map = m_memalign(4096,len);
   memset(cpu->exec_blk_map,0,len);


   len = PPC_JIT_PHYS_HASH_SIZE * sizeof(void *);
   cpu->exec_phys_map = m_memalign(4096,len);
   memset(cpu->exec_phys_map,0,len);


   if (!(area_size = cpu->vm->exec_area_size))
      area_size = PPC_EXEC_AREA_SIZE;


   cpu->exec_page_area_size = area_size * 1048576;
   cpu->exec_page_area = memzone_map_exec_area(cpu->exec_page_area_size);

   if (!cpu->exec_page_area) {
      fprintf(stderr,
              "ppc32_jit_init: unable to create exec area (size %lu)\n",
              (u_long)cpu->exec_page_area_size);
      return(-1);
   }


   cpu->exec_page_count = cpu->exec_page_area_size / PPC_JIT_BUFSIZE;

   cpu->exec_page_array = calloc(cpu->exec_page_count,
                                 sizeof(insn_exec_page_t));

   if (!cpu->exec_page_array) {
      fprintf(stderr,"ppc32_jit_init: unable to create exec page array\n");
      return(-1);
   }

   for(i=0,cp_addr=cpu->exec_page_area;i<cpu->exec_page_count;i++) {
      cp = &cpu->exec_page_array[i];

      cp->ptr = cp_addr;
      cp_addr += PPC_JIT_BUFSIZE;

      cp->next = cpu->exec_page_free_list;
      cpu->exec_page_free_list = cp;
   }

   printf("CPU%u: carved JIT exec zone of %lu Mb into %lu pages of %u Kb.\n",
          cpu->gen->id,
          (u_long)(cpu->exec_page_area_size / 1048576),
          (u_long)cpu->exec_page_count,PPC_JIT_BUFSIZE / 1024);
   return(0);
}
