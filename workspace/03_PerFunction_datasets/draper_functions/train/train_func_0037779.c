sysKill(pid_, signal_)
int pid_;
A signal_;
{
  int aSignal;
  if (SymbolToEnum(SignalEnums, signal_, &aSignal)) {
    (void)pa((V)signal_);
    q = ERR_DOMAIN;
    R 0;
  } else
    R (I)kill((pid_t)pid_, aSignal);
}
