range_coder_init_decoder(range_coder_t *coder, int fd,
			unpack_data_t *unpack_data)
{
	int i;
	coder->low = coder->code = 0;
	coder->range = (unsigned int) -1;

	for (i=0; i < 4 ; i++) {
		coder->code = (coder->code << 8) | rar_get_char(fd, unpack_data);
	}
}
