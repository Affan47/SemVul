read_from_oldmem(char *buf, size_t count,
				u64 *ppos, int userbuf)
{
	unsigned long pfn, offset;
	size_t nr_bytes;
	ssize_t read = 0, tmp;

	if (!count)
		return 0;

	offset = (unsigned long)(*ppos % PAGE_SIZE);
	pfn = (unsigned long)(*ppos / PAGE_SIZE);

	do {
		if (count > (PAGE_SIZE - offset))
			nr_bytes = PAGE_SIZE - offset;
		else
			nr_bytes = count;


		if (pfn_is_ram(pfn) == 0)
			memset(buf, 0, nr_bytes);
		else {
			tmp = copy_oldmem_page(pfn, buf, nr_bytes,
						offset, userbuf);
			if (tmp < 0)
				return tmp;
		}
		*ppos += nr_bytes;
		count -= nr_bytes;
		buf += nr_bytes;
		read += nr_bytes;
		++pfn;
		offset = 0;
	} while (count);

	return read;
}
