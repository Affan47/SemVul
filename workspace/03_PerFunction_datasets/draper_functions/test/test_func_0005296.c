checkURLs(message *mainMessage, mbox_ctx *mctx, mbox_status *rc, int is_html)
{
	blob *b;
	tag_arguments_t hrefs;

	if(*rc == VIRUS)
		return;

	hrefs.scanContents = mctx->ctx->engine->dboptions&CL_DB_PHISHING_URLS && (DCONF_PHISHING & PHISHING_CONF_ENGINE);

	if(!hrefs.scanContents)


		return;

	hrefs.count = 0;
	hrefs.tag = hrefs.value = NULL;
	hrefs.contents = NULL;

	b = getHrefs(mainMessage, &hrefs);
	if(b) {
		if(hrefs.scanContents) {
			if(phishingScan(mctx->ctx, &hrefs) == CL_VIRUS) {


				mainMessage->isInfected = TRUE;
				*rc = VIRUS;
				cli_dbgmsg("PH:Phishing found\n");
			}
		}
	}
	hrefs_done(b,&hrefs);
}
