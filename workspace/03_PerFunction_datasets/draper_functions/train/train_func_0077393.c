SetAvailInfo( ChewingData *pgdata, int begin, int end)
{
	AvailInfo *pai = &( pgdata->availInfo );
	const uint16_t *phoneSeq = pgdata->phoneSeq;
	int nPhoneSeq = pgdata->nPhoneSeq;
	const int *bSymbolArrBrkpt = pgdata->bSymbolArrBrkpt;

	int pho_id;
	int diff;
	uint16_t userPhoneSeq[ MAX_PHONE_SEQ_LEN ];

	int i, head, head_tmp;
	int tail, tail_tmp;

	head = tail = 0;

	pai->nAvail = 0;

	if ( pgdata->config.bPhraseChoiceRearward ) {
		for ( i = end; i >= begin; i--){
			head = i;
			if ( bSymbolArrBrkpt[ i ] )
				break;
		}
		head_tmp = end;
	} else {
		head_tmp = head = begin;
	}

	if ( pgdata->config.bPhraseChoiceRearward ) {
		tail_tmp = tail = end;
	} else {
		for ( i = begin; i < nPhoneSeq; i++ ) {
			if ( bSymbolArrBrkpt[ i ] )
				break;
			tail = i;
		}
		tail_tmp = begin;
	}

	while ( head <= head_tmp && tail_tmp <= tail ) {
		diff = tail_tmp - head_tmp;
		pho_id = TreeFindPhrase( pgdata, head_tmp, tail_tmp, phoneSeq );

		if ( pho_id != -1 ) {

			pai->avail[ pai->nAvail ].len = diff + 1;
			pai->avail[ pai->nAvail ].id = pho_id;
			pai->nAvail++;
		}
		else {
			memcpy(
				userPhoneSeq,
				&phoneSeq[ head_tmp ],
				sizeof( uint16_t ) * ( diff + 1 ) ) ;
			userPhoneSeq[ diff + 1 ] = 0;
			if ( UserGetPhraseFirst( pgdata, userPhoneSeq ) ) {

				pai->avail[ pai->nAvail ].len = diff + 1;
				pai->avail[ pai->nAvail ].id = -1;
				pai->nAvail++;
			} else {
				pai->avail[ pai->nAvail ].len = 0;
				pai->avail[ pai->nAvail ].id = -1;
			}
		}

		if ( pgdata->config.bPhraseChoiceRearward ) {
			head_tmp--;
		} else {
			tail_tmp++;
		}
	}
}
