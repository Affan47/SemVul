playFile (u_int id)
{
    fxAssert (id < conf.playList.length(), "ESC_PLAY: internal playlist ID to large")

    const fxStr& filename = conf.playList[id];
    protoTrace("Playing file \"%s\".", (const char*) filename);

    int fd = open((const char*) filename, O_RDONLY);
    if (fd < 0) {
	protoTrace("Unable to open file \"%s\" for reading.", (const char*) filename);
	return;
    }

    u_char buf[1024];
    int len;
    u_int pos;
    do {
	pos = 0;
	do {
	    len = read(fd, &buf[pos], 1);
	    if (buf[pos] == DLE)
		buf[++pos] = DLE;
	    pos++;
	} while (len > 0 &&  pos < sizeof(buf) - 1);
	putModem(&buf[0], pos, getDataTimeout());
    } while (len > 0);
    close(fd);
}
