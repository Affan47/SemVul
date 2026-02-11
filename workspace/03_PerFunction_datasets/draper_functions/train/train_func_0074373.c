Reverse(BitString *b)
{
	BitString *result;
	size_t i,j;

	if (b == NULL)		return NULL;
	result = Create(b->count);
    if (result == NULL) {
        iError.RaiseError("iBitString.Reverse",CONTAINER_ERROR_NOMEMORY);
        return NULL;
    }
	result->count = b->count;
	i = 0;
	j = b->count-1;
	while (i < result->count) {
		if (b->contents[j >> 3] & (1 << (j&7))) {
			result->contents[i >> 3] |= (1 << (i&7));
		}
		i++;
		j--;
	}
	return result;
}
