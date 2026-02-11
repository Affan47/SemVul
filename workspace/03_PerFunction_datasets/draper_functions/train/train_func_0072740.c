log_archive_flags (void) {
  uintL flags = 0
#  ifdef DB_ARCH_REMOVE
    | (missingp(STACK_(0)) ? 0 : DB_ARCH_REMOVE)
#  endif
#  ifdef DB_ARCH_LOG
    | (missingp(STACK_(1)) ? 0 : DB_ARCH_LOG)
#  endif
#  ifdef DB_ARCH_DATA
    | (missingp(STACK_(2)) ? 0 : DB_ARCH_DATA)
#  endif
#  ifdef DB_ARCH_ABS
    | (missingp(STACK_(3)) ? 0 : DB_ARCH_ABS)
#  endif
   ;
  skipSTACK(4);
  return flags;
}
