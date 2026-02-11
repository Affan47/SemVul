trapInit()
{


  if (signal(SIGTERM, trapSig) == SIG_ERR) { trapSig (C_SIGTFLT); }


  if (   (signal(SIGFPE , trapSig) == SIG_ERR)
      || (signal(SIGBUS , trapSig) == SIG_ERR)
      || (signal(SIGSEGV, trapSig) == SIG_ERR)) trapSig (C_SIGTFLT);
}
