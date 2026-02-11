process_zinfo_pack ( struct input_file *input,
				struct output_file *output,
				union zinfo_record *zinfo ) {
	struct zinfo_pack *pack = &zinfo->pack;
	size_t offset = pack->offset;
	size_t len = pack->len;
	unsigned long packed_len;

	if ( ( offset + len ) > input->len ) {
		fprintf ( stderr, "Input buffer overrun on pack\n" );
		return -1;
	}

	output->len = align ( output->len, pack->align );
	if ( output->len > output->max_len ) {
		fprintf ( stderr, "Output buffer overrun on pack\n" );
		return -1;
	}

	if ( ucl_nrv2b_99_compress ( ( input->buf + offset ), len,
				     ( output->buf + output->len ),
				     &packed_len, 0 ) != UCL_E_OK ) {
		fprintf ( stderr, "Compression failure\n" );
		return -1;
	}

	if ( DEBUG ) {
		fprintf ( stderr, "PACK [%#zx,%#zx) to [%#zx,%#zx)\n",
			  offset, ( offset + len ), output->len,
			  ( size_t )( output->len + packed_len ) );
	}

	output->len += packed_len;
	if ( output->len > output->max_len ) {
		fprintf ( stderr, "Output buffer overrun on pack\n" );
		return -1;
	}

	return 0;
}
