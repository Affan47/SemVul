aligned_vwrite(char *buf, char *addr, unsigned long count)
{
	struct page *p;
	int copied = 0;

	while (count) {
		unsigned long offset, length;

		offset = offset_in_page(addr);
		length = PAGE_SIZE - offset;
		if (length > count)
			length = count;
		p = vmalloc_to_page(addr);


		if (p) {


			void *map = kmap_atomic(p);
			memcpy(map + offset, buf, length);
			kunmap_atomic(map);
		}
		addr += length;
		buf += length;
		copied += length;
		count -= length;
	}
	return copied;
}
