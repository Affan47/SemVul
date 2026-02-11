octeon_droq_compute_max_packet_bufs(struct octeon_droq *droq)
{
	u32 count = 0;


	droq->max_empty_descs = 0;

	do {
		droq->max_empty_descs++;
		count += droq->buffer_size;
	} while (count < (64 * 1024));

	droq->max_empty_descs = droq->max_count - droq->max_empty_descs;
}
