serialio_set_footled (serialio_data_t* serialio, int led){
	int status;
        if (serialio->fd){
                ioctl(serialio->fd, TIOCMGET, &status);
		if (led > 0) status &= ~TIOCM_RTS; else status |= TIOCM_RTS;
		ioctl(serialio->fd, TIOCMSET, &status);
                return TIOCM_RTS;
        }else return -1;
}
