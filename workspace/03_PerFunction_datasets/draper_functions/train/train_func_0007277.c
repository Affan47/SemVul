waitForMore(int msecs, bool *timeout)
{
  resetError();
  qint64 retval = socketDevice()->waitForMore(msecs, timeout);
  if (retval == -1)
    {
      copyError();
      emit gotError(error());
    }
  return retval;
}
