memlog_dump(cpu_gen_t *cpu)
{
   memlog_access_t *acc;
   char s_data[64];
   u_int i,pos;

   for(i=0;i<MEMLOG_COUNT;i++) {
      pos = cpu->memlog_pos + i;
      pos &= (MEMLOG_COUNT-1);
      acc = &cpu->memlog_array[pos];

      if (cpu_get_pc(cpu)) {
         if (acc->data_valid)
            snprintf(s_data,sizeof(s_data),"0x%llx",acc->data);
         else
            snprintf(s_data,sizeof(s_data),"XXXXXXXX");

         printf("CPU%u: pc=0x%8.8llx, vaddr=0x%8.8llx, "
                "size=%u, type=%s, data=%s\n",
                cpu->id,acc->iaddr,acc->vaddr,acc->op_size,
                (acc->op_type == MTS_READ) ? "read " : "write",
                s_data);
      }
   }
}
