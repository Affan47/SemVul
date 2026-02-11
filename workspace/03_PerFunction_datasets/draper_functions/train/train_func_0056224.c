check_crc(pb_file *pbf, const char *stream, ub4 usize) {
	uint32_t crc=0;
	uint32_t lcrc;
	ub1 scratch[16];

	crc = crc32(crc, NULL, 0);
	crc = crc32(crc, (const unsigned char *)stream, usize);
	if(pb_read(pbf, scratch, 16) != 16) {
		perror("read");
        exit(EXIT_FAILURE);
	}
	if(UNPACK_UB4(scratch, 0) != 0x08074b50) {
		fprintf(stderr, "Error! Missing data descriptor!\n");
		exit(EXIT_FAILURE);
	}
	lcrc = UNPACK_UB4(scratch, 4);
	if(crc != lcrc){
    	fprintf(stderr, "Error! CRCs do not match! Got %" PRIx32
                        ", expected %" PRIx32 "\n",
                crc, lcrc);
      	exit(EXIT_FAILURE);
    }
}
