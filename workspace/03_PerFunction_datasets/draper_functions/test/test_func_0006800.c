pt_topa_dump(struct pt_buffer *buf)
{
	struct topa *topa;

	list_for_each_entry(topa, &buf->tables, list) {
		int i;

		pr_debug("# table @%p (%016Lx), off %llx size %zx\n", topa->table,
			 topa->phys, topa->offset, topa->size);
		for (i = 0; i < TENTS_PER_PAGE; i++) {
			pr_debug("# entry @%p (%lx sz %u %c%c%c) raw=%16llx\n",
				 &topa->table[i],
				 (unsigned long)topa->table[i].base << TOPA_SHIFT,
				 sizes(topa->table[i].size),
				 topa->table[i].end ?  'E' : ' ',
				 topa->table[i].intr ? 'I' : ' ',
				 topa->table[i].stop ? 'S' : ' ',
				 *(u64 *)&topa->table[i]);
			if ((pt_cap_get(PT_CAP_topa_multiple_entries) &&
			     topa->table[i].stop) ||
			    topa->table[i].end)
				break;
		}
	}
}
