libmpq__decompress_huffman(uint8_t *in_buf, uint32_t in_size, uint8_t *out_buf, uint32_t out_size) {


	int32_t tb     = 0;
	struct huffman_tree_s *ht;
	struct huffman_input_stream_s *is;


	if ((ht = malloc(sizeof(struct huffman_tree_s))) == NULL ||
	    (is = malloc(sizeof(struct huffman_input_stream_s))) == NULL) {


		return LIBMPQ_ERROR_MALLOC;
	}


	memset(ht, 0, sizeof(struct huffman_tree_s));
	memset(is, 0, sizeof(struct huffman_input_stream_s));


	is->bit_buf  = *(uint32_t *)in_buf;
	in_buf      += sizeof(int32_t);
	is->in_buf   = (uint8_t *)in_buf;
	is->bits     = 32;


	libmpq__huffman_tree_init(ht, LIBMPQ_HUFF_DECOMPRESS);


	tb = libmpq__do_decompress_huffman(ht, is, out_buf, out_size);


	free(is);
	free(ht);


	return tb;
}
