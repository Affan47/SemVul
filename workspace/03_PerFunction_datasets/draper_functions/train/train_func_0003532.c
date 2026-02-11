write( const char *s, streamsize n)
{
    _stream.next_in = (Byte*)s;
    _stream.avail_in = (uInt)n;

    while( _stream.avail_in != 0)
    {
	if( deflate(&_stream, Z_NO_FLUSH) != Z_OK)
	{
	    LOG_ERROR << "Compression error!" << endl;
	    break;
	}
	if( _stream.avail_out == 0)
	{
	    _flush();
	}
    }
    return n-_stream.avail_in;
}
