dbg_hex_dump_da ( unsigned long dispaddr, const void *data,
		       unsigned long len ) {
	unsigned int offset;

	for ( offset = 0 ; offset < len ; offset += 16 ) {
		dbg_hex_dump_da_row ( dispaddr, data, len, offset );
	}
}
