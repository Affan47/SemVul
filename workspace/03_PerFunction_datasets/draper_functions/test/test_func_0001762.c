ldr_show_pot_line(struct db_main *db, char *line)
{
	char *ciphertext, *pos;
	int hash;
	struct db_cracked *current, *last;

	ciphertext = ldr_get_field(&line);

	if (line) {

		if (!fmt_list->next &&
		    !fmt_list->methods.valid(ciphertext, fmt_list))
			return;

		pos = line;
		do {
			if (*pos == '\r' || *pos == '\n') *pos = 0;
		} while (*pos++);

		if (db->options->flags & DB_PLAINTEXTS) {
			list_add(db->plaintexts, line);
			return;
		}

		hash = ldr_cracked_hash(ciphertext);

		last = db->cracked_hash[hash];
		current = db->cracked_hash[hash] =
			mem_alloc_tiny(sizeof(struct db_cracked),
			MEM_ALIGN_WORD);
		current->next = last;

		current->ciphertext = str_alloc_copy(ciphertext);
		current->plaintext = str_alloc_copy(line);
	}
}
