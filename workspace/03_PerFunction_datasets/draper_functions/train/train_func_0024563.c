stream_compare(void *a, void *b)
{
	struct ctf_file_stream *s_a = a, *s_b = b;

	if (s_a->parent.real_timestamp < s_b->parent.real_timestamp) {
		return 1;
	} else if (likely(s_a->parent.real_timestamp > s_b->parent.real_timestamp)) {
		return 0;
	} else {
		return strcmp(s_a->parent.path, s_b->parent.path);
	}
}
