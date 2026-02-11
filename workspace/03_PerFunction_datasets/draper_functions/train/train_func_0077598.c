reset()
{
	delete[]data;
	data = new char[1];
	data[0] = '\0';
	delete[]compresseddata;
	compresseddata = NULL;
	buffer_length = 0;
	compressed_buffer_length = 0;
	if (tempfilefd > -1) {
		close(tempfilefd);
		if (!preservetemp) {
			unlink(tempfilepath.toCharArray());
		}
		tempfilefd = -1;
		tempfilesize = 0;
	}
	bytesalreadysent = 0;
	dontsendbody = false;
	preservetemp = false;
	decompress = "";
}
