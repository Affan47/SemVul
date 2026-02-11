IO_UpdateParity(reader* globalData, char parity) {

  struct termios newtio;


  tcgetattr(globalData->io.handle,&newtio);


  switch (parity) {


    case 'O':
      newtio.c_cflag |= PARODD;
      break;


    case 'E':
      newtio.c_cflag &= (~PARODD);
      break;


    case 'N':
      break;
  }


  if(tcflush(globalData->io.handle, TCIFLUSH) < 0) {
    close(globalData->io.handle);
    return -1;
   }


  if(tcsetattr(globalData->io.handle, TCSANOW, &newtio) < 0) {
    close(globalData->io.handle);
    return -1;
  }


  globalData->io.parity = parity;

  return(globalData->io.parity);
}
