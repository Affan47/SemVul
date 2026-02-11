scan_for_rsdp(uintptr_t addr, uint32_t length)
{
   rsdp_t *rp;
   uintptr_t end = addr + length;


   while ((uintptr_t)addr < end) {
      rp = (rsdp_t*)addr;
      if (*(unsigned int *)addr == RSDPSignature &&
		checksum((unsigned char*)addr, rp->length) == 0) {
	   return rp;
      }
      addr += 4;
   }
   return NULL;
}
