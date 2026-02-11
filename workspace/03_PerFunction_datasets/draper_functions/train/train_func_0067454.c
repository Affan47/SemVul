add_chunks(chunk_t a, chunk_t b)
{
	u_int16_t sum;
	u_int8_t rem = 0;
	ssize_t i, j;

	for (i = a.len - 1, j = b.len -1; i >= 0 && j >= 0; i--, j--)
	{
		sum = a.ptr[i] + b.ptr[j] + rem;
		a.ptr[i] = (u_char)sum;
		rem = sum >> 8;
	}
	for (; i >= 0 && rem; i--)
	{
		sum = a.ptr[i] + rem;
		a.ptr[i] = (u_char)sum;
		rem = sum >> 8;
	}
}
