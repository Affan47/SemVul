ChoicePrevAvail( ChewingContext *ctx )
{
	ChewingData *pgdata = ctx->data;
	if (pgdata->choiceInfo.isSymbol != WORD_CHOICE) return 0;
	if ( ++( pgdata->availInfo.currentAvail ) >= pgdata->availInfo.nAvail )
		pgdata->availInfo.currentAvail = 0;
	SetChoiceInfo( pgdata );
	return 0;
}
