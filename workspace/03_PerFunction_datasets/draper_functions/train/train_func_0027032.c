chewing_handle_CtrlNum( ChewingContext *ctx, int key )
{
	ChewingData *pgdata = ctx->data;
	ChewingOutput *pgo = ctx->output;
	int keystrokeRtn = KEYSTROKE_ABSORB;
	int newPhraseLen;
	int i;
	uint16 addPhoneSeq[ MAX_PHONE_SEQ_LEN ];
	char addWordSeq[ MAX_PHONE_SEQ_LEN * MAX_UTF8_SIZE + 1 ];
	int phraseState;
	int cursor;

	CheckAndResetRange( pgdata );

	if ( pgdata->bSelect )
		return 0;

	CallPhrasing( pgdata );
	newPhraseLen = key - '0';

	if ( key == '0' || key == '1' ) {
		pgdata->bSelect = 1;
		pgdata->choiceInfo.oldChiSymbolCursor = pgdata->chiSymbolCursor;

		HaninSymbolInput(
				&( pgdata->choiceInfo ),
				&( pgdata->availInfo ),
				pgdata->phoneSeq,
				pgdata->config.candPerPage );
		CallPhrasing( pgdata );
		MakeOutputWithRtn( pgo, pgdata, keystrokeRtn );
		return 0;
	}

	cursor = PhoneSeqCursor( pgdata );
	if ( ! pgdata->config.bAddPhraseForward ) {
		if (
			newPhraseLen >= 1 &&
			cursor + newPhraseLen - 1 <= pgdata->nPhoneSeq ) {
			if ( NoSymbolBetween(
				pgdata,
				cursor,
				cursor + newPhraseLen - 1 ) ) {

				memcpy( addPhoneSeq,
				        &pgdata->phoneSeq[ cursor ],
				        sizeof( uint16 ) * newPhraseLen );
				addPhoneSeq[ newPhraseLen ] = 0;
				ueStrNCpy( addWordSeq,
				           ueStrSeek( (char *) &pgdata->phrOut.chiBuf,
				                      cursor ),
				           newPhraseLen, 1);


				phraseState = UserUpdatePhrase( addPhoneSeq, addWordSeq );
				SetUpdatePhraseMsg(
					pgdata,
					addWordSeq,
					newPhraseLen,
					phraseState );


				for ( i = 1; i < newPhraseLen; i++ )
					pgdata->bUserArrBrkpt[ cursor + i ] = 0;
			}
		}
	}
	else {
		if (
			newPhraseLen >= 1 &&
			cursor - newPhraseLen >= 0 ) {
			if ( NoSymbolBetween( pgdata,
			                      cursor,
			                      cursor - newPhraseLen ) ) {

				memcpy( addPhoneSeq,
				        &pgdata->phoneSeq[ cursor - newPhraseLen ],
				        sizeof( uint16 ) * newPhraseLen );
				addPhoneSeq[ newPhraseLen ] = 0;
				ueStrNCpy( addWordSeq,
				           ueStrSeek( (char *) &pgdata->phrOut.chiBuf,
				           cursor - newPhraseLen ),
				           newPhraseLen, 1);

				phraseState = UserUpdatePhrase( addPhoneSeq, addWordSeq );
				SetUpdatePhraseMsg(
					pgdata,
					addWordSeq,
					newPhraseLen,
					phraseState );


				for ( i = 1; i < newPhraseLen; i++ )
					pgdata->bUserArrBrkpt[ cursor - newPhraseLen + i ] = 0;
			}
		}
	}
	CallPhrasing( pgdata );
	MakeOutputWithRtn( pgo, pgdata, keystrokeRtn );
	MakeOutputAddMsgAndCleanInterval( pgo, pgdata );
	return 0;
}
