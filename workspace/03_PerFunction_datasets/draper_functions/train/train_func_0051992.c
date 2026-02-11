wi_file_decompress_at_path(wi_file_t *file, wi_string_t *path) {
	FILE 	*source;
	FILE 	*dest;

	int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];


    if (NULL == (source = fdopen(file->fd, "r")))
    	return false;

    if (NULL == (dest = fopen(wi_string_cstring(path), "rw")))
    	return false;


    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;


    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }
        if (strm.avail_in == 0)
            break;
        strm.next_in = in;


        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);

            if(ret == Z_STREAM_ERROR);
            	continue;

            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return ret;
            }
            have = CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);


    } while (ret != Z_STREAM_END);


    (void)inflateEnd(&strm);


	fclose(source);
	fclose(dest);

    return (ret == Z_STREAM_END) ? true : false;
}
