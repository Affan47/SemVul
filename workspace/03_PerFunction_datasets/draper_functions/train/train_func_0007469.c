cram_uncompress_block(cram_block *b) {
    char *uncomp;
    size_t uncomp_size = 0;

    if (b->uncomp_size == 0) {

	b->method = RAW;
	return 0;
    }

    switch (b->method) {
    case RAW:
	b->uncomp_size = b->comp_size;
	return 0;

    case GZIP:
	uncomp = zlib_mem_inflate((char *)b->data, b->comp_size, &uncomp_size);
	if (!uncomp)
	    return -1;
	if ((int)uncomp_size != b->uncomp_size)
	    return -1;
	free(b->data);
	b->data = (unsigned char *)uncomp;
	b->method = RAW;
	break;

#ifdef HAVE_LIBBZ2
    case BZIP2: {
	unsigned int usize = b->uncomp_size;
	if (!(uncomp = malloc(usize)))
	    return -1;
	if (BZ_OK != BZ2_bzBuffToBuffDecompress(uncomp, &usize,
						(char *)b->data, b->comp_size,
						0, 0)) {
	    free(uncomp);
	    return -1;
	}
	b->data = (unsigned char *)uncomp;
	b->method = RAW;
	b->uncomp_size = usize;
	break;
    }
#else
    case BZIP2:
	fprintf(stderr, "Bzip2 compression is not compiled into this "
		"version.\nPlease rebuild and try again.\n");
	return -1;
#endif

    case BM_ERROR:
    default:
	return -1;
    }

    return 0;
}
