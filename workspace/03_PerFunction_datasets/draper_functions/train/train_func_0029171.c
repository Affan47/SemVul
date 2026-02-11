GetTypeSize(uint8 type)
{
	enum {Bytes, KB, MB, GB};
	int size;

	switch(type) {
		case Bytes: size = 1; break;
		case KB: size = 1024; break;
		case MB: size = 1048576; break;
		case GB: size = 1073741824; break;
		default: size = -1; break;
	}
	return size;
}
