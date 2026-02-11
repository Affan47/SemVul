iallocm(size_t usize, size_t alignment, bool zero)
{

	assert(usize == ((alignment == 0) ? s2u(usize) : sa2u(usize, alignment,
	    NULL)));

	if (alignment != 0)
		return (ipalloc(usize, alignment, zero));
	else if (zero)
		return (icalloc(usize));
	else
		return (imalloc(usize));
}
