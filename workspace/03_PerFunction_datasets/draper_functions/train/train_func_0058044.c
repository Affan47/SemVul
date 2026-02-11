SPF_c_ensure_capacity(void **datap, size_t *sizep, size_t length)
{
	size_t		 size = *sizep;
	if (length > size)
		size = length + (length / 4);
	if (size > *sizep) {
		void	*tmp = realloc(*datap, size);
		if (!tmp)
			return -1;

		*datap = tmp;
		*sizep = size;
	}
	return 0;
}
