tcsetpgrp(int fd, pid_t pgrp)
{
  WRAPPER_EXECUTION_DISABLE_CKPT();

  pid_t currPgrp = originalToCurrentPid( pgrp );

  int retVal = _real_tcsetpgrp(fd, currPgrp);


  WRAPPER_EXECUTION_ENABLE_CKPT();

  return retVal;
}
