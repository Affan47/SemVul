physmem_copy_to_vm(vm_instance_t *vm,void *real_buffer,
                        m_uint64_t paddr,size_t len)
{
   m_uint64_t dummy;
   m_uint32_t r;
   u_char *ptr;

   while(len > 0) {
      r = m_min(VM_PAGE_SIZE - (paddr & VM_PAGE_IMASK), len);
      ptr = physmem_get_hptr(vm,paddr,0,MTS_WRITE,&dummy);

      if (likely(ptr != NULL)) {
         memcpy(ptr,real_buffer,r);
      } else {
         r = m_min(len,4);
         switch(r) {
            case 4:
               physmem_copy_u32_to_vm(vm,paddr,
                                      htovm32(*(m_uint32_t *)real_buffer));
               break;
            case 2:
               physmem_copy_u16_to_vm(vm,paddr,
                                      htovm16(*(m_uint16_t *)real_buffer));
               break;
            case 1:
               physmem_copy_u8_to_vm(vm,paddr,*(m_uint8_t *)real_buffer);
               break;
         }
      }

      real_buffer += r;
      paddr += r;
      len -= r;
   }
}
