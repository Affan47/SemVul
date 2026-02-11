tb_blit(unsigned int x, unsigned int y, unsigned int w, unsigned int h, const struct tb_cell *cells)
{
	if (x+w >= back_buffer.width || y+h >= back_buffer.height)
		return;

	unsigned int sy;
	struct tb_cell *dst = &CELL(&back_buffer, x, y);
	size_t size = sizeof(struct tb_cell) * w;

	for (sy = 0; sy < h; ++sy) {
		memcpy(dst, cells, size);
		dst += back_buffer.width;
		cells += w;
	}
}
