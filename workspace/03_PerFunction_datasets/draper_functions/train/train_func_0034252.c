arm9_prefetch16( void *data, u32 adr) {
#ifdef PROFILE_MEMORY_ACCESS
  profile_memory_access( 1, adr, PROFILE_PREFETCH);
#endif

#ifdef EARLY_MEMORY_ACCESS
  if((adr & ~0x3FFF) == MMU.DTCMRegion)
    {

      return T1ReadWord(ARM9Mem.ARM9_DTCM, adr & 0x3FFF);
    }

  if ( (adr & 0x0f000000) == 0x02000000) {
    return T1ReadWord( MMU.MMU_MEM[ARMCPU_ARM9][(adr >> 20) & 0xFF],
                       adr & MMU.MMU_MASK[ARMCPU_ARM9][(adr >> 20) & 0xFF]);
  }
#endif

  return MMU_read16( ARMCPU_ARM9, adr);
}
