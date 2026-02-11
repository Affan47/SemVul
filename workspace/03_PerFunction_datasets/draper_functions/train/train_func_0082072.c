GRecvArr (void)
{
    unsigned len;
    char *arr;
    unsigned const char *up;

    if (!(len = (unsigned) GRecvInt()))
	return (char *)0;
    if (len < 4) {
	message ("Too short binary authentication data block\n");
	exit(15);
    }
    if (len > 0x10000 || !(arr = malloc (len))) {
	message ("No memory for read buffer\n");
	exit(15);
    }
    GRead (arr, len);
    up = (unsigned const char *)arr;
    if (len != (unsigned)(up[3] | (up[2] << 8) | (up[1] << 16) | (up[0] << 24))) {
	message ("Mismatched binary authentication data block size\n");
	exit(15);
    }
    return arr;
}
