untile(struct buffer *pixels, struct dim dim)
{

	u8 tmp_px[dim.height][dim.width];


	int x, y, tx, ty, cx, cy, i;
	i = 0;
	for (y = 0; y < dim.height / 8; y++) {
	for (x = 0; x < dim.width / 8; x++) {
		for (ty = 0; ty < 8; ty++) {
		for (tx = 0; tx < 8; tx++) {
			cy = y * 8 + ty;
			cx = x * 8 + tx;
			tmp_px[cy][cx] = pixels->data[i];
			i++;
		}
		}
	}
	}

	memcpy(pixels->data, tmp_px, pixels->size);
}
