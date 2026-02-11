setRTS(bool value)
{
	int status=0;

	if (handle>=0) {
		if(ioctl(handle,TIOCMGET,&status)<0){
			D(bug("Serialport: Can't get status"));
		}
		if(value)status|=TIOCM_RTS;
		else status&=~TIOCM_RTS;
		ioctl(handle,TIOCMSET,&status);
	}
}
