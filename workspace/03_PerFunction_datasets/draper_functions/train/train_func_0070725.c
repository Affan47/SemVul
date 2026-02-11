openPort(ArRobot *robot, const char *host, int port)
{
  int ret;
  std::string str;
  if ((ret = myConn.open(host, port)) != 0)
  {
    str = myConn.getOpenMessage(ret);
    ArLog::log(ArLog::Terse, "ArACTS_1_2: Could not connect to ACTS running on %s:%d (%s)", host, port, str.c_str());
    return false;

  }
  myRequested = false;
  setRobot(robot);
  return true;
}
