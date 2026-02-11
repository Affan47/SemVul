huge_allocated(struct header *head, unsigned long offset)
{
	unsigned long i;
	struct huge_alloc *ha;

	for (i = head->huge; i; i = ha->next) {
		ha = (void *)((char *)head + i);
		if (ha->off <= offset && ha->off + ha->len > offset)
			return true;
	}
	return false;
}
