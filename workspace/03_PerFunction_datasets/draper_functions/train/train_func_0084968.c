chewing_handle_ShiftLeft( ChewingContext *ctx )
{
	ChewingData *pgdata = ctx->data;
	ChewingOutput *pgo = ctx->output;
	int keystrokeRtn = KEYSTROKE_ABSORB;

	if ( ! ChewingIsEntering( pgdata ) ) {
		keystrokeRtn = KEYSTROKE_IGNORE;
	}
	if ( ! pgdata->bSelect ) {

		if (
			! ZuinIsEntering( &( pgdata->zuinData ) ) &&
			pgdata->chiSymbolCursor > 0 &&
			pgdata->PointEnd > -9 ) {
			if ( pgdata->PointStart == -1 )
				pgdata->PointStart = pgdata->chiSymbolCursor;
			pgdata->chiSymbolCursor--;
			if (
				ChewingIsChiAt( pgdata->chiSymbolCursor, pgdata ) ) {
				pgdata->PointEnd--;
			}
			if ( pgdata->PointEnd == 0 )
				pgdata->PointStart = -1;
		}
	}

	MakeOutputWithRtn( pgo, pgdata, keystrokeRtn );
	return 0;
}
