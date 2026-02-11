physmem_copy_from_vm(vm_instance_t *vm,void *real_buffer,
                          m_uint64_t paddr,size_t len)
{
   m_uint64_t dummy;
   m_uint32_t r;
   u_char *ptr;

   while(len > 0) {
      r = m_min(VM_PAGE_SIZE - (paddr & VM_PAGE_IMASK), len);
      ptr = physmem_get_hptr(vm,paddr,0,MTS_READ,&dummy);

      if (likely(ptr != NULL)) {
         memcpy(real_buffer,ptr,r);
      } else {
         r = m_min(len,4);
         switch(r) {
            case 4:
               *(m_uint32_t *)real_buffer =
                  htovm32(physmem_copy_u32_from_vm(vm,paddr));
               break;
            case 2:
               *(m_uint16_t *)real_buffer =
                  htovm16(physmem_copy_u16_from_vm(vm,paddr));
               break;
            case 1:
               *(m_uint8_t *)real_buffer = physmem_copy_u8_from_vm(vm,paddr);
               break;
         }
      }

      real_buffer += r;
      paddr += r;
      len -= r;
   }
}
