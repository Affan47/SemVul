chardb_txt_save(struct mmo_charstatus *st)
{
	int idx;

	nullpo_retr(false, st);

	idx = char_id2idx(st->char_id);
	if(idx >= 0) {
		if(char_dat[idx].st.account_id == st->account_id) {
			memcpy(&char_dat[idx].st, st, sizeof(struct mmo_charstatus));
#ifdef TXT_JOURNAL
			if( char_journal_enable )
				journal_write( &char_journal, st->char_id, &char_dat[idx] );
#endif
		}
	}
	return true;
}
