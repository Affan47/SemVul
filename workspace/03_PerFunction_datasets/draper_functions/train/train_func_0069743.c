requestQuit(void)
{
  const char c = '1';
  if (myConn.getStatus() != ArDeviceConnection::STATUS_OPEN)
  {
    ArLog::log(ArLog::Verbose,
	       "ArACTS_1_2::requestQuit: No connection to ACTS.\n");
    return false;
  }
  return myConn.write(&c, 1);
}
