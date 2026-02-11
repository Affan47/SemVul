array_search_forward (const unsigned char *data, unsigned int size,
                      const unsigned char *marker, unsigned int msize)
{
	while (size >= msize) {
		if (memcmp (data, marker, msize) == 0)
			return data;
		size--;
		data++;
	}
	return NULL;
}
