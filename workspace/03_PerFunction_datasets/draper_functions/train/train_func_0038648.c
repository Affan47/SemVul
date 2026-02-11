ctf_metadata_trace_pre_handler(struct bt_stream_pos *ppos,
			struct bt_trace_descriptor *td)
{
	struct ctf_text_stream_pos *pos =
		container_of(ppos, struct ctf_text_stream_pos, parent);
	struct ctf_trace *trace;

	trace = container_of(td, struct ctf_trace, parent);
	if (!trace->metadata_string)
		return -EINVAL;
	if (trace->metadata_packetized) {
		fprintf(pos->fp, "/* CTF %u.%u */\n",
			BT_CTF_MAJOR, BT_CTF_MINOR);
	}
	fprintf(pos->fp, "%s", trace->metadata_string);
	return 0;
}
