UserGetPhraseFirst( ChewingData *pgdata, const uint16_t phoneSeq[] )
{
	pgdata->prev_userphrase = HashFindPhonePhrase( pgdata, phoneSeq, NULL );
	if ( ! pgdata->prev_userphrase )
		return NULL;
	return &( pgdata->prev_userphrase->data );
}
