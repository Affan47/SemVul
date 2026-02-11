loadHistoryData()
{
	Q_ASSERT(this->history);
	Q_ASSERT(this->accounts);
	AB_IMEXPORTER_CONTEXT *ctx;


	this->history->clearAll();


	ctx = abt_parser::load_local_ctx(settings->getHistoryFilename(),
					 "ctxfile", "default");
	abt_parser::parse_ctx(ctx, this->accounts, this->history);
	AB_ImExporterContext_free(ctx);
}
