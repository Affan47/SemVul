sendZData(int fdin, int fdout)
{
    z_stream zstream;
    zstream.zalloc = NULL;
    zstream.zfree = NULL;
    zstream.opaque = NULL;
    zstream.data_type = Z_BINARY;
    if (deflateInit(&zstream, Z_DEFAULT_COMPRESSION) == Z_OK) {
	char obuf[16*1024];
	zstream.next_out = (Bytef*) obuf;
	zstream.avail_out = sizeof (obuf);

	int cc;
	for (;;) {
	    char buf[16*1024];
	    cc = read(fdin, buf, sizeof (buf));
	    if (cc == 0)
		break;
	    if (cc < 0) {
		perror_reply(551, "Error reading input file", errno);
		goto bad;
	    }
	    zstream.next_in = (Bytef*) buf;
	    zstream.avail_in = cc;
	    do {
		if (deflate(&zstream, Z_NO_FLUSH) != Z_OK) {
		    reply(452, "Compressor error: %s", zstream.msg);
		    goto bad;
		}
		if (zstream.avail_out == 0) {
		    if (write(fdout, obuf, sizeof (obuf)) != sizeof (obuf)) {
			perror_reply(426, "Data connection", errno);
			goto bad;
		    }
		    byte_count += sizeof (obuf);
		    zstream.next_out = (Bytef*) obuf;
		    zstream.avail_out = sizeof (obuf);
		}
	    } while (zstream.avail_in > 0);
	}
	int state;
	do {
	    switch (state = deflate(&zstream, Z_FINISH)) {
	    case Z_STREAM_END:
	    case Z_OK:
		if (zstream.avail_out != sizeof (obuf)) {
		    cc = sizeof (obuf) - zstream.avail_out;
		    if (write(fdout, obuf, cc) != cc) {
			perror_reply(426, "Data connection", errno);
			goto bad;
		    }
		    byte_count += cc;
		    zstream.next_out = (Bytef*) obuf;
		    zstream.avail_out = sizeof (obuf);
		}
		break;
	    default:
		reply(426, "Compressor error: %s", zstream.msg);
		goto bad;
	    }
	} while (state != Z_STREAM_END);
	deflateEnd(&zstream);
	return (true);
bad:
	deflateEnd(&zstream);
    } else
	reply(452, "Can not initialize compression library: %s", zstream.msg);
    return (false);
}
