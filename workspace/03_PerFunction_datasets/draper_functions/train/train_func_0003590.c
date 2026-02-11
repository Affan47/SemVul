G_fpcompress_writeXdrDouble(int fd, char *src, int nofNum, int precision,
			    char *compressBuf, int useRle, int useLzw)
{
    if (!G_fpcompress_writeXdrNums(fd, src, nofNum, precision, compressBuf, 0,
				   useRle, useLzw)) {
	G3d_error
	    ("G_fpcompress_writeXdrDouble: error in G_fpcompress_writeXdrNums");
	return 0;
    }

    return 1;
}
