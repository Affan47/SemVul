sparse_file_callback(struct sparse_file *s, bool sparse, bool crc,
		int (*write)(void *priv, const void *data, int len), void *priv)
{
	int ret;
	int chunks;
	struct output_file *out;

	chunks = sparse_count_chunks(s);
	out = output_file_open_callback(write, priv, s->block_size, s->len, false,
			sparse, chunks, crc);

	if (!out)
		return -ENOMEM;

	ret = write_all_blocks(s, out);

	output_file_close(out);

	return ret;
}
