rateToBaud(int rate)
{
  switch (rate) {
  case 300: return B300;
  case 1200: return B1200;
  case 1800: return B1800;
  case 2400: return B2400;
  case 4800: return B4800;
  case 9600: return B9600;
  case 19200: return B19200;
  case 38400: return B38400;
  case 57600: return B57600;
  case 115200: return B115200;
  default:
    ArLog::log(ArLog::Terse, "ArSerialConnection::rateToBaud: Did not know baud for rate %d.", rate);
    return -1;
  }
}
