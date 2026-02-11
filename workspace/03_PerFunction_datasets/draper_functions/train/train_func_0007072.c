transmit(double* samples, int count)
{
	try {
		notifier->setEnabled(false);
		unsigned char buf[count];
		for(int i=0; i<count; i++) {
			buf[i]=static_cast<unsigned char>
				(samples[i]*(fm?240.0:63.0));
		}
		tcflush(device,TCIFLUSH);
		if(write(device,buf,count)!=count) {
			throw Error();
		}
		notifier->setEnabled(true);
	} catch(Error) {
		close();
	}
}
