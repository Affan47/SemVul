tegra_slink_calculate_curr_xfer_param(
	struct spi_device *spi, struct tegra_slink_data *tspi,
	struct spi_transfer *t)
{
	unsigned remain_len = t->len - tspi->cur_pos;
	unsigned max_word;
	unsigned bits_per_word;
	unsigned max_len;
	unsigned total_fifo_words;

	bits_per_word = t->bits_per_word;
	tspi->bytes_per_word = DIV_ROUND_UP(bits_per_word, 8);

	if (bits_per_word == 8 || bits_per_word == 16) {
		tspi->is_packed = 1;
		tspi->words_per_32bit = 32/bits_per_word;
	} else {
		tspi->is_packed = 0;
		tspi->words_per_32bit = 1;
	}
	tspi->packed_size = tegra_slink_get_packed_size(tspi, t);

	if (tspi->is_packed) {
		max_len = min(remain_len, tspi->max_buf_size);
		tspi->curr_dma_words = max_len/tspi->bytes_per_word;
		total_fifo_words = max_len/4;
	} else {
		max_word = (remain_len - 1) / tspi->bytes_per_word + 1;
		max_word = min(max_word, tspi->max_buf_size/4);
		tspi->curr_dma_words = max_word;
		total_fifo_words = max_word;
	}
	return total_fifo_words;
}
