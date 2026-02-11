writeHeader( )
{
    if( !base->isWritable() )
    {

	int newFlags = lastFlags | O_RDWR;
	if( base->open( newFlags ) < 0 )
	{
	    rDebug("writeHeader failed to re-open for write");
	    return false;
	}
    }

    if(fileIV == 0)
	rError("Internal error: fileIV == 0 in writeHeader!!!");
    rDebug("writing fileIV %" PRIu64 , fileIV);

    unsigned char buf[8] = {0};
    for(int i=0; i<8; ++i)
    {
	buf[sizeof(buf)-1-i] = (unsigned char)(fileIV & 0xff);
	fileIV >>= 8;
    }

    cipher->streamEncode( buf, sizeof(buf), externalIV, key );

    IORequest req;
    req.offset = 0;
    req.data = buf;
    req.dataLen = 8;

    base->write( req );

    return true;
}
