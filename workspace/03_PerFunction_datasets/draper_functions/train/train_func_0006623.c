read_code(LHALH1Decoder *decoder, uint16_t *result)
{
	unsigned int node_index;
	int bit;


	node_index = 0;


	while (!decoder->nodes[node_index].leaf) {
		bit = read_bit(&decoder->bit_stream_reader);

		if (bit < 0) {
			return 0;
		}


		node_index = decoder->nodes[node_index].child_index
		           - (unsigned int) bit;
	}

	*result = decoder->nodes[node_index].child_index;


	increment_for_code(decoder, *result);

	return 1;
}
