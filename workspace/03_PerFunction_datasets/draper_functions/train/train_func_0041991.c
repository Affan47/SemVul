trace_seq_printf(struct trace_seq *s, const char *fmt, ...)
{
	unsigned int save_len = s->seq.len;
	va_list ap;

	if (s->full)
		return;

	__trace_seq_init(s);

	va_start(ap, fmt);
	seq_buf_vprintf(&s->seq, fmt, ap);
	va_end(ap);


	if (unlikely(seq_buf_has_overflowed(&s->seq))) {
		s->seq.len = save_len;
		s->full = 1;
	}
}
