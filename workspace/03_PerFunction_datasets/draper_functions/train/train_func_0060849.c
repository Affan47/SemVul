chewing_handle_Up( ChewingContext *ctx )
{
	ChewingData *pgdata = ctx->data;
	ChewingOutput *pgo = ctx->output;
	int keystrokeRtn = KEYSTROKE_ABSORB;
	int key_buf_cursor;

	CheckAndResetRange( pgdata );

	if ( ! ChewingIsEntering( pgdata ) ) {
		keystrokeRtn = KEYSTROKE_IGNORE;
	}

	key_buf_cursor = pgdata->chiSymbolCursor;

	if ( pgdata->chiSymbolCursor == pgdata->chiSymbolBufLen )
		key_buf_cursor--;


	if ( ! pgdata->symbolKeyBuf[ key_buf_cursor ] ) {

		chewing_handle_Esc(ctx);
	}

	MakeOutputWithRtn( pgo, pgdata, keystrokeRtn );
	return 0;
}
