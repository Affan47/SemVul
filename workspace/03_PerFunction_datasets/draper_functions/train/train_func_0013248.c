chewing_aux_String( ChewingContext *ctx )
{
	int i;
	char *msg = (char *) calloc(
		1 + ctx->output->showMsgLen,
		sizeof(char) * MAX_UTF8_SIZE );
	for ( i = 0; i < ctx->output->showMsgLen; ++i )
		strcat( msg, (char *)(ctx->output->showMsg[ i ].s) );
	return msg;

}
