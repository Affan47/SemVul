load(const char *fileName)
{
    struct stat stbuf;
    memset( &stbuf, 0, sizeof(struct stat));
    if( lstat( fileName, &stbuf ) != 0)
	return false;

    int size = stbuf.st_size;

    int fd = open( fileName, O_RDONLY );
    if(fd < 0)
	return false;

    char *buf = new char[size];

    int res = ::read( fd, buf, size );
    close( fd );

    if( res != size )
    {
	rWarning("Partial read of config file, expecting %i bytes, got %i",
		size, res);
	delete[] buf;
	return false;
    }

    ConfigVar in;
    in.write( (unsigned char *)buf, size );
    delete[] buf;

    return loadFromVar( in );
}
