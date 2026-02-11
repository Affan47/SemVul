pa_4b_access(cpu_gen_t *cpu,struct vdevice *dev,m_uint32_t offset,
                   u_int op_size,u_int op_type,m_uint64_t *data)
{
   struct pa_4b_data *d = dev->priv_data;
   __maybe_unused static m_uint32_t test1,test2,test3;

   if (op_type == MTS_READ)
      *data = 0xFFFFFFFF;

#if DEBUG_ACCESS
   if (offset >= MUNICH32_MEM_SIZE) {
      if (op_type == MTS_READ) {
         cpu_log(cpu,d->name,"read  access to offset = 0x%x, pc = 0x%llx "
                 "(op_size=%u)\n",offset,cpu_get_pc(cpu),op_size);
      } else {
         cpu_log(cpu,d->name,"write access to vaddr = 0x%x, pc = 0x%llx, "
                 "val = 0x%llx (op_size=%u)\n",
                 offset,cpu_get_pc(cpu),*data,op_size);
      }
   }
#endif


   switch(offset) {
      case 0x40008:
         if (op_type == MTS_READ)
            *data = 0xFF;
         break;

      case 0x40030:
         if (op_type == MTS_READ)
            *data = 0xFF;
         break;

      case 0x40000:
         if (op_type == MTS_READ)
            *data = 0xFFFF;
         break;

      case 0x40020:
         if (op_type == MTS_READ)
            *data = 0xFFFFFFFF;
         else
            test2 = *data;
         break;

      case 0x40021:
         if (op_type == MTS_READ)
            *data = 0xFF;
         else
            test3 = *data;
         break;

      case 0x40023:
         if (op_type == MTS_READ)
            *data = 0xFF;
         break;

      case 0x40040:
         if (op_type == MTS_READ)
            *data = 0x04;
         break;


      case 0x40044:
         if (op_type == MTS_READ)
            *data = 0xFF;
         break;


      case 0x40050:
         if (op_type == MTS_WRITE) {
            test1 = *data;
         } else {
            switch(test1) {
               case TP3420_SID_PUP:
                  *data = TP3420_SR_AI;
                  vm_set_irq(d->vm,C7200_PA_MGMT_IRQ);
                  break;
               case TP3420_SID_ENST:
                  *data = 0xB0;
                  break;
               default:
                  *data = 0x03;
                  break;
            }
         }
         break;

      default:
         if (offset < MUNICH32_MEM_SIZE)
            return(m32_gen_access(&d->m32_data,cpu,offset - d->m32_offset,
                                  op_size,op_type,data));
   }

   return NULL;
}
