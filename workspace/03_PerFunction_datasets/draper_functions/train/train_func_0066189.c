SerialRead(unsigned char * buffer, int numBytes){
	int bytesRead = 0;

	if(fd > 0)
		if((bytesRead = read(fd, buffer, numBytes)) < 0)

			printf("Serial read of %d bytes failed - Error number: %d\n", numBytes, errno);


	return(bytesRead);
}
