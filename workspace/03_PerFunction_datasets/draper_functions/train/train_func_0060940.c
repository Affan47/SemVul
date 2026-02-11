process_elf32_notes(void *note_buf, unsigned long size_note)
{
	Elf32_Nhdr *nt;
	size_t index, len = 0;
	int num = 0;


	for (index = 0; index < size_note; index += len) {
		nt = note_buf + index;

		if(nt->n_type == NT_PRSTATUS) {
			dd->nt_prstatus_percpu[num] = nt;
			num++;
		}
		len = sizeof(Elf32_Nhdr);
		len = roundup(len + nt->n_namesz, 4);
		len = roundup(len + nt->n_descsz, 4);
	}

	if (num > 0) {
		pc->flags2 |= ELF_NOTES;
		dd->num_prstatus_notes = num;
	}
	return;
}
