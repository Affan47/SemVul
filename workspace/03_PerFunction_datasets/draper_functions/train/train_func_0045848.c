zio_open_raw(Zio *zio, const char *file_name)
{
#ifdef ENABLE_EBNET
    if (is_ebnet_url(file_name)) {
	zio->is_ebnet = 1;
	zio->file = ebnet_open(file_name);
    } else {
	zio->is_ebnet = 0;
	zio->file = open(file_name, O_RDONLY | O_BINARY);
    }
#else
    zio->file = open(file_name, O_RDONLY | O_BINARY);
#endif

    return zio->file;
}
