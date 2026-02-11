set_echo_off(FILE *fp, struct termios *attr)
{

  if (tcgetattr(fileno(fp), attr) != 0)
	return(-1);
  attr->c_lflag &= ~(ECHO);
  if (tcsetattr(fileno(fp), TCSAFLUSH | TCSASOFT, attr) != 0)
	return(-1);

  return(0);
}
