replay(int delay)
{
  if (logflag&2) return;
  log_in=get_user_file(3);
  if (filevalid(log_in,fLOG)) {
    logflag|=2;
    logdelay=delay;
  }
}
