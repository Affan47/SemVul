slot_dump(struct list_head *head)
{
	struct slot *s;

	list_for_each_entry(s, head, slot_siblings)
		if (s) {
			dprintf("Slot %d Information\n", s->slot_addr);
			dprintf("  Last Addr: %d\n", s->last_addr);
			dprintf("  Type: %d\n", s->element_type);
			dprintf("  Barcode: %s\n", s->barcode);
			if (s->drive_tid) {
				dprintf("  TID : %d\n", s->drive_tid);
				dprintf("  LUN : %" PRIu64 "\n", s->drive_lun);
			}
			dprintf("  ASC/ASCQ : %d\n\n", s->asc);
		}
}
