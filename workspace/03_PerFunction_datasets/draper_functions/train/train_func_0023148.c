ctf_convert_index_timestamp(struct bt_trace_descriptor *tdp)
{
	int i, j, k;
	struct ctf_trace *td = container_of(tdp, struct ctf_trace, parent);


	for (i = 0; i < td->streams->len; i++) {
		struct ctf_stream_declaration *stream_class;

		stream_class = g_ptr_array_index(td->streams, i);
		if (!stream_class)
			continue;

		for (j = 0; j < stream_class->streams->len; j++) {
			struct ctf_stream_definition *stream;
			struct ctf_stream_pos *stream_pos;
			struct ctf_file_stream *cfs;

			stream = g_ptr_array_index(stream_class->streams, j);
			if (!stream)
				continue;
			cfs = container_of(stream, struct ctf_file_stream,
					parent);
			stream_pos = &cfs->pos;
			if (!stream_pos->packet_index)
				continue;

			for (k = 0; k < stream_pos->packet_index->len; k++) {
				struct packet_index *index;

				index = &g_array_index(stream_pos->packet_index,
						struct packet_index, k);
				index->ts_real.timestamp_begin =
					ctf_get_real_timestamp(stream,
							index->ts_cycles.timestamp_begin);
				index->ts_real.timestamp_end =
					ctf_get_real_timestamp(stream,
							index->ts_cycles.timestamp_end);
			}
		}
	}
	return 0;
}
