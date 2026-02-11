cpucpy2d(uint32_t *src, unsigned src_stride, unsigned src_x, unsigned src_y,
		     uint32_t *dst, unsigned dst_stride, unsigned dst_x, unsigned dst_y,
		     unsigned logical_tile_no)
{
	int i, j;
	int failed = 0;

	for (i = 0; i < options.tile_size; i++) {
		for (j = 0; j < options.tile_size; j++) {
			unsigned dst_ofs = dst_x + j + dst_stride * (dst_y + i);
			unsigned src_ofs = src_x + j + src_stride * (src_y + i);
			unsigned expect = logical_tile_no*options.tile_size*options.tile_size
			    + i*options.tile_size + j;
			uint32_t tmp = src[src_ofs];
			if (tmp != expect) {
			    printf("mismatch at tile %i pos %i, read %i, expected %i, diff %i\n",
				    logical_tile_no, i*options.tile_size + j, tmp, expect, (int) tmp - expect);
			    if (options.trace_tile >= 0 && options.fail)
				    exit(1);
			    failed++;
			}

			dst[dst_ofs] = expect;
		}
	}
	if (failed && options.fail)
		exit(1);

	if (failed > stats.max_failed_reads)
		stats.max_failed_reads = failed;
	if (failed)
		stats.num_failed++;
}
