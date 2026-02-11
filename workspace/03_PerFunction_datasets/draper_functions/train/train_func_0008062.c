setcom(void) {
  stbuf.c_cflag &= ~(CBAUD | CSIZE | CSTOPB | CLOCAL | PARENB);
  stbuf.c_cflag |= (speed | bits | CREAD | clocal | parity | stopbits );
  if (ioctl(comfd, TCSETA, &stbuf) < 0) {
    serror("Can't ioctl set device",1);
  }
}
