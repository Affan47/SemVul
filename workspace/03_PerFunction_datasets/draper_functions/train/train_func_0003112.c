sendCommandAndRecvStatus(
	const char *command, const char *commandDesc,
	char *buf, unsigned int size, unsigned int msWait)
{
  bool ret;
  ArTime start;


  if (!writeLine(command))
  {
    ArLog::log(ArLog::Normal, "%s: Could not send %s", getName(),
	       commandDesc);
    return false;
  }


  if (!readLine(buf, size, msWait))
  {
    ArLog::log(ArLog::Normal, "%s: Received no response to %s (in %d but really %d)",
	       getName(), commandDesc, msWait, start.mSecSince());
    return false;
  }


  if (strcasecmp(buf, command) != 0)
  {
    ArLog::log(ArLog::Normal, "%s: Received bad echo to %s (command %s got back %s)",
	       getName(), commandDesc, command, buf);
    return false;
  }


  if (!readLine(buf, size, msWait))
  {
    ArLog::log(ArLog::Normal,
	       "%s: Did not receive status back from %s",
	       getName(), commandDesc);
    return false;
  }

  return true;
}
