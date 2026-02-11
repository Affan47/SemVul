cloog_stride_malloc()
{
	CloogStride *s;

	s = ALLOC(CloogStride);
	if (!s)
		cloog_die("memory overflow.\n");

	s->references = 1;
	cloog_int_init(s->stride);
	cloog_int_init(s->offset);
	cloog_int_init(s->factor);
	s->constraint = cloog_constraint_invalid();

	return s;
}
