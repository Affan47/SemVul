del_from_list(struct header *head,
			  u16 *list, struct page_header *ph, unsigned sp_bits)
{

	if (ph->prev == 0) {
		*list = ph->next;
	} else {
		struct page_header *prev = from_pgnum(head, ph->prev, sp_bits);
		prev->next = ph->next;
	}
	if (ph->next != 0) {
		struct page_header *next = from_pgnum(head, ph->next, sp_bits);
		next->prev = ph->prev;
	}
}
