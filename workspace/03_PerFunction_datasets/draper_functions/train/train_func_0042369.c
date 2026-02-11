db_get_options (void) {
  uintL flags = 0
#  ifdef DB_RMW
    | (missingp(STACK_(0)) ? 0 : DB_RMW)
#  endif
#  ifdef DB_MULTIPLE
    | (missingp(STACK_(1)) ? 0 : DB_MULTIPLE)
#  endif
#  ifdef DB_READ_UNCOMMITTED
    | (missingp(STACK_(2)) ? 0 : DB_READ_UNCOMMITTED)
#  endif
#  ifdef DB_READ_COMMITTED
    | (missingp(STACK_(3)) ? 0 : DB_READ_COMMITTED)
#  endif
#  ifdef DB_AUTO_COMMIT
    | (missingp(STACK_(4)) ? 0 : DB_AUTO_COMMIT)
#  endif
   ;
  skipSTACK(5);
  return flags;
}
