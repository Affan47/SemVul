internalOpen(void)
{
  struct termios tio;

  if (myStatus == STATUS_OPEN)
  {
    ArLog::log(ArLog::Terse, "ArSerialConnection::open: Serial port already open");
    return OPEN_ALREADY_OPEN;
  }


  if ((myPort = ::open(myPortName.c_str(),O_RDWR | O_NDELAY)) < 0)
  {
    ArLog::log(ArLog::Terse, "ArSerialConnection::open: Could not open serial port '%s'", myPortName.c_str());
    return OPEN_COULD_NOT_OPEN_PORT;
  }


  if (tcgetattr(myPort, &tio) != 0)
  {
    ArLog::log(ArLog::Terse, "ArSerialConnection::open: Could not get port data to set up port");
    close();
    myStatus = STATUS_OPEN_FAILED;
    return OPEN_COULD_NOT_SET_UP_PORT;
  }


  tio.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);


  tio.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);


  tio.c_cflag &= ~(CSIZE | PARENB);


  tio.c_cflag |= CS8;


  tio.c_oflag &= ~(OPOST);


  tio.c_cc[VTIME] = 0;
  tio.c_cc[VMIN] = 0;

  if (tcsetattr(myPort,TCSAFLUSH,&tio) < 0)
  {
    ArLog::log(ArLog::Terse,
	       "ArSerialConnection::open: Could not set up port");
    close();
    myStatus = STATUS_OPEN_FAILED;
    return OPEN_COULD_NOT_SET_UP_PORT;
  }

  myStatus = STATUS_OPEN;

  if (rateToBaud(myBaudRate) == -1)
  {
    ArLog::log(ArLog::Terse, "ArSerialConnection::open: Invalid baud rate.");
    close();
    myStatus = STATUS_OPEN_FAILED;
    return OPEN_INVALID_BAUD_RATE;
  }

  if (!setBaud(myBaudRate))
  {
    ArLog::log(ArLog::Terse,
	       "ArSerialConnection::open: Could not set baud rate.");
    close();
    myStatus = STATUS_OPEN_FAILED;
    return OPEN_COULD_NOT_SET_BAUD;
  }

  if (!setHardwareControl(myHardwareControl))
  {
    ArLog::log(ArLog::Terse,
	       "ArSerialConnection::open: Could not set hardware control.");
    close();
    myStatus = STATUS_OPEN_FAILED;
    return OPEN_COULD_NOT_SET_UP_PORT;
  }

  ArLog::log(ArLog::Verbose, "ArSerialConnection::open: Successfully opened and configured serial port.");
  return 0;
}
