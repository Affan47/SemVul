copy_string20(unpack_data_t *unpack_data, unsigned int length, unsigned int distance)
{
	unsigned int dest_ptr;

	unpack_data->last_dist = unpack_data->old_dist[unpack_data->old_dist_ptr++ & 3] = distance;
	unpack_data->last_length = length;
	unpack_data->dest_unp_size -= length;

	dest_ptr = unpack_data->unp_ptr - distance;
	if (dest_ptr < MAXWINSIZE-300 && unpack_data->unp_ptr < MAXWINSIZE-300) {
		unpack_data->window[unpack_data->unp_ptr++] = unpack_data->window[dest_ptr++];
		unpack_data->window[unpack_data->unp_ptr++] = unpack_data->window[dest_ptr++];
		while (length > 2) {
			length--;
			unpack_data->window[unpack_data->unp_ptr++] = unpack_data->window[dest_ptr++];
		}
	} else while (length--) {
		unpack_data->window[unpack_data->unp_ptr] = unpack_data->window[dest_ptr++ & MAXWINMASK];
		unpack_data->unp_ptr = (unpack_data->unp_ptr+1) & MAXWINMASK;
	}
}
