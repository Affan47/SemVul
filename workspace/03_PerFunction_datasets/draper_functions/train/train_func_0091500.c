setLIDARControl(unsigned char *val)
{
MTX_IOREQ req;

  if (!myEnabled)
    return false;

	req.myReg = MTX_LIDAR_CTRL;
	req.mySize = sizeof(unsigned char);
	req.myData.myVal8 = *val;

	if (ioctl(myFD, MTX_WRITE_REG, &req) != 0)
  {
    ArLog::log(ArLog::Normal, "ArMTXIO::setLIDARControl() failed to set LIDAR ControlRegister");
    return false;
  }

  return true;

}
