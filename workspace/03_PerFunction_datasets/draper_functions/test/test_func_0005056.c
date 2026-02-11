gsbm_zero_mask(struct BM *map)
{
    int numbytes;
    unsigned char *buf;

    numbytes = map->bytes * map->rows;
    buf = map->data;

    while (numbytes--) {
	*buf++ = 0;
    }

    return;
}
