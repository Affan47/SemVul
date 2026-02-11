syssyslog(apriority, message)
  A	apriority;
  C	*message;
{
  unsigned long	priority;

  if (SymbolsToMask(SyslogMasks, apriority, &priority) == -1) {
    (void)pa((V)apriority);
    q = ERR_DOMAIN;
    R 0;
  }
  syslog(priority, message);
  R 1;
}
