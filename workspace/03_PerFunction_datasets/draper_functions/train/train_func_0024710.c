X28_open_data_link(char* device){
    int fd = -1, iret;
    struct termios tios;
    info(0,"open serial device %s",device);
    fd = open(device, O_RDWR|O_NONBLOCK|O_NOCTTY);
    if(fd==-1) {
	error(errno, "sema_open_data_link: error open(2)ing the character device <%s>",
	      device);
	if(errno == EACCES)
	    error(0, "sema_open_data_link: user has no right to access the serial device");
	return -1;
    }

    tcgetattr(fd, &tios);
    cfsetospeed(&tios, B4800);
    cfsetispeed(&tios, B4800);
    kannel_cfmakeraw(&tios);
    tios.c_iflag |= IGNBRK|IGNPAR|INPCK|ISTRIP;
    tios.c_cflag |= (CSIZE|HUPCL | CREAD | CRTSCTS);
    tios.c_cflag ^= PARODD;
    tios.c_cflag |=CS7;
    iret = tcsetattr(fd, TCSANOW, &tios);
    if(iret == -1){
	error(errno,"sema_open_data_link: fail to set termios attribute");
	goto error;
    }
    tcflush(fd, TCIOFLUSH);
    return fd;

error:
    return -1;
}
