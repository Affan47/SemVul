demultiplex_view(struct view *view)
{
	struct stream *stream, *prev = NULL, *next;

	for (stream = streams; stream; stream = next) {
		next = stream->next;
		if (stream->view == view)
			stream_destroy(stream, prev);
		else
			prev = stream;
	}
	child_close(view);
}
