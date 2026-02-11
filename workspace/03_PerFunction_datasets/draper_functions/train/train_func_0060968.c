upbuf(BW *bw)
{
	B *b;
	b = bprev();
	if (b == bw->b) {
		b = bprev();
	}
	return get_buffer_in_window(bw, b);
}
