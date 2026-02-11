setSocketBuffer(int fd, int bufSize)
{
    int bval, blen=sizeof(bval);


    if (getsockopt(fd,SOL_SOCKET,SO_RCVBUF,&bval,&blen)==0 && bval<bufSize) {
	bval=bufSize;
	(void)setsockopt(fd,SOL_SOCKET,SO_RCVBUF,&bval,blen);
    }
    if (getsockopt(fd,SOL_SOCKET,SO_SNDBUF,&bval,&blen)==0 && bval<bufSize) {
	bval=bufSize;
	(void)setsockopt(fd,SOL_SOCKET,SO_SNDBUF,&bval,blen);
    }
}
