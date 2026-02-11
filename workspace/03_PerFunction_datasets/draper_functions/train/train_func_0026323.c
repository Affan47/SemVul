setSigv(I flag){sigvFlag=(0==flag)?0:(2==flag)?2:1;
  if(sigvFlag)aplus_signal(SIGSEGV,SIG_DFL);else aplus_signal(SIGSEGV,sigv);}
