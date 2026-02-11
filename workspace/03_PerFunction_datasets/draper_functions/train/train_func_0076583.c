discard(int n)
{
    if (n <= 0)
	return;
    for (size_t j = 0; j < (size_t)n && j < buffer.nstrings; ++j)
	str_free(buffer.string[j]);
    if (n >= (int)buffer.nstrings)
	buffer.nstrings = 0;
    else
    {
	for (size_t k = n; k < buffer.nstrings; ++k)
    	    buffer.string[k - n] = buffer.string[k];

	buffer.nstrings -= n;
    }
}
