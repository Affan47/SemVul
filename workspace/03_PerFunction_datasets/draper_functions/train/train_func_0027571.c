jbd2_journal_test_revoke(journal_t *journal,
			unsigned long long blocknr,
			tid_t sequence)
{
	struct jbd2_revoke_record_s *record;

	record = find_revoke_record(journal, blocknr);
	if (!record)
		return 0;
	if (tid_gt(sequence, record->sequence))
		return 0;
	return 1;
}
