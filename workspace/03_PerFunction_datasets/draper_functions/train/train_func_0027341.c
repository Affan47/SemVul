exists (void)
{
#if defined (ACE_MT_SAFE) && (ACE_MT_SAFE != 0)
# if defined (ACE_HAS_THREAD_SPECIFIC_STORAGE) || \
     defined (ACE_HAS_TSS_EMULATION)
  void *tss_log_msg = 0;


  return ACE_Log_Msg::key_created_
    && ACE_Thread::getspecific (*(log_msg_tss_key ()), &tss_log_msg) != -1
    && tss_log_msg != 0;
# else
#   error "Platform must support thread-specific storage if threads are used."
# endif
#else
  return 1;
#endif
}
