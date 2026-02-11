M_Allocate_Stacks(void)
{
  unsigned length = 0;
  WamWord *addr;
  int i;
  WamWord *addr_to_try[] = {
#ifndef MMAP_NEEDS_FIXED
    NULL,
#endif
#ifdef M_MMAP_HIGH_ADR1
    (WamWord *) M_MMAP_HIGH_ADR1,
#endif
#ifdef M_MMAP_HIGH_ADR2
    (WamWord *) M_MMAP_HIGH_ADR2,
#endif
#ifdef M_MMAP_HIGH_ADR3
    (WamWord *) M_MMAP_HIGH_ADR3,
#endif
    (WamWord *) -1 };

  page_size = getpagesize() / sizeof(WamWord);

  for (i = 0; i < NB_OF_STACKS; i++)
    {
      stk_tbl[i].size = Round_Up(stk_tbl[i].size, page_size);
      length += stk_tbl[i].size + page_size;
    }
  length *= sizeof(WamWord);

  addr = NULL;
  for(i = 0; addr == NULL && addr_to_try[i] != (WamWord *) -1; i++)
    {
      addr = addr_to_try[i];
#ifdef DEBUG
      DBGPRINTF("trying at high addr: %p --> ", addr);
#endif
      if (addr)
	{
	  addr = (WamWord *) Round_Down((long) addr, getpagesize());
	  addr -= length;
	}
#ifdef DEBUG
      DBGPRINTF("base: %p length: %d\n", addr, length);
#endif
      addr = Virtual_Mem_Alloc(addr, length);
#ifdef DEBUG
      DBGPRINTF("obtaining: %p\n", addr);
#endif
#if TAG_SIZE_HIGH > 0
      if (addr && (((unsigned long) (addr) + length) >> (WORD_SIZE - TAG_SIZE_HIGH)) != 0)
	{
#ifdef DEBUG
	  DBGPRINTF("  -> invalid high bits addr\n");
#endif
	  Virtual_Mem_Free(addr, length);
	  addr = NULL;
	}
#endif
    }

  if (addr == NULL)
    Fatal_Error(ERR_STACKS_ALLOCATION);

  for (i = 0; i < NB_OF_STACKS; i++)
    {
      stk_tbl[i].stack = addr;
      addr += stk_tbl[i].size;
      Virtual_Mem_Protect(addr, page_size);
      addr += page_size;
    }

#if defined(M_sparc_solaris) || defined(M_ix86_solaris) || \
    defined(M_ix86_sco) || defined(M_mips_linux) || defined(M_x86_64_linux)
  {
    struct sigaction act;

    act.sa_sigaction = (void (*)()) SIGSEGV_Handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;

    sigaction(SIGSEGV, &act, NULL);
  }

#elif !defined(_WIN32) && !defined(__CYGWIN__)
  signal(SIGSEGV, (void (*)()) SIGSEGV_Handler);
#endif
}
