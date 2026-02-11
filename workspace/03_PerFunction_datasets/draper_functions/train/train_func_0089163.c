sysfcntl(fd, acmd, arg)
  I	fd;
  A	acmd;
  I	arg;
{
  unsigned long	cmd;
  if (SymbolToEnum(FcntlEnums, acmd, &cmd)) {
    (void)pa((V)acmd);
    q = ERR_DOMAIN;
    R 0;
  } else
    R (I)fcntl((int)fd, (int)cmd, (int)arg);
}
