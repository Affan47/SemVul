process(const char *fname) {
	FILE *fp;
	pd_code_e pdc;
	asn1c_integer_t offset = 0;
	ber_tlv_len_t frame_size = 0;

	if(strcmp(fname, "-")) {
		fp = fopen(fname, "rb");
		if(!fp) {
			perror(fname);
			return -1;
		}
	} else {
		fp = stdin;
	}


	for(; offset < skip_bytes; offset++) {
		if(fgetc(fp) == -1) {
			fprintf(stderr,
				"%s: input source (%" PRIdASN " bytes) "
				"has less data than \"-s %d\" switch "
				"wants to skip\n",
				fname, offset, skip_bytes);
			if(fp != stdin) fclose(fp);
			return -1;
		}
	}


	do {
		pdc = process_deeper(fname, fp, &offset,
				     0, -1, &frame_size, 0, 0);
	} while(pdc == PD_FINISHED && !single_type_decoding);

	if(fp != stdin)
		fclose(fp);

	if(pdc == PD_FAILED)
		return -1;
	return 0;
}
