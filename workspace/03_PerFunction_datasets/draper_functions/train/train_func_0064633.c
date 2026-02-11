free_pending_data(void)
{
	struct datablock *p, *head = mbr_pending_data_head;
	while (head) {
		p = head;
		head = head->next;
		free(p);
	}
	mbr_pending_data_head = NULL;
	mbr_pending_data_tail = NULL;
}
