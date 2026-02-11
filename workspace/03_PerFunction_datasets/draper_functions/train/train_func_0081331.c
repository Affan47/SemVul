buffer_copy_bytes(uint32_t len)
{
	uint32_t in;
	while (len > 0 && !feof(infile) && !ferror(infile)) {
		in = len < COPY_BUFFER_LEN ? len : COPY_BUFFER_LEN;
		in = fread(byte_buffer, 1, in, infile);
		len -= in;
		fwrite(byte_buffer, 1, in, stdout);
		if (ferror(stdout)) {
			buffer_skip_bytes(len);
			return;
		}
	}
}
