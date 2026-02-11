setLinger(int time)
{
  struct linger lin;
  myError = NoErr;
  myErrorStr.clear();

  if (time)
  {
    lin.l_onoff=1;
    lin.l_linger=time;
  }
  else
  {
    lin.l_onoff=0;
    lin.l_linger=time;
  }

  if (setsockopt(myFD, SOL_SOCKET, SO_LINGER, &lin, sizeof(lin)) != 0)
  {
    myErrorStr="Failure to setsockopt LINGER";
    myError = NetFail;
    ArLog::logErrorFromOS(ArLog::Normal,
			  "ArSocket::setLinger: setsockopt failed");
    return(false);
  }
  else
    return(true);
}
