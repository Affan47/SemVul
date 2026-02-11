convert(struct state *st)
{
	int *p;
	int i, j;
	st->fast_from = calloc(1, sizeof(int)*((st->buffer_map->bytes_per_line/st->bpp_size)*(2*st->radius+st->speed+2) + 2*st->radius+st->speed+2));
	if (st->fast_from == NULL) {
		perror("distort");
		exit(EXIT_FAILURE);
	}
	p = st->fast_from;
	for (i = 0; i < 2*st->radius+st->speed+2; i++) {
		for (j = 0; j < 2*st->radius+st->speed+2; j++) {
			*(p + i + j*st->buffer_map->bytes_per_line/st->bpp_size)
				= st->from[i][j][0] + st->xgwa.width*st->from[i][j][1];
			if (*(p + i + j*st->buffer_map->bytes_per_line/st->bpp_size) < 0
					|| *(p + i + j*st->buffer_map->bytes_per_line/st->bpp_size) >= st->orig_map->height*st->orig_map->width) {
				*(p + i + j*st->buffer_map->bytes_per_line/st->bpp_size) = 0;
			}
		}
	}
}
