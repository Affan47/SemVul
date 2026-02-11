read_block_data(uint8_t* data, struct BlockArray* arrayp)
{
	int32_t blocks = arrayp->columns * arrayp->rows;
	arrayp->data = calloc(blocks, sizeof(struct ColorBlock));
	size_t pos = 0;

	for (int32_t i=0;i<blocks;i++) {
		for (int32_t u=0;u<3;u++) {
			pos += compress_block_decode(data+pos, &arrayp->data[i].chan[u]);
		}
	}

	return pos;
}
