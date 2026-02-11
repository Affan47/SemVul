find_revoke_record(journal_t *journal,
						      unsigned long long blocknr)
{
	struct list_head *hash_list;
	struct jbd2_revoke_record_s *record;

	hash_list = &journal->j_revoke->hash_table[hash(journal, blocknr)];

	spin_lock(&journal->j_revoke_lock);
	record = (struct jbd2_revoke_record_s *) hash_list->next;
	while (&(record->hash) != hash_list) {
		if (record->blocknr == blocknr) {
			spin_unlock(&journal->j_revoke_lock);
			return record;
		}
		record = (struct jbd2_revoke_record_s *) record->hash.next;
	}
	spin_unlock(&journal->j_revoke_lock);
	return NULL;
}
