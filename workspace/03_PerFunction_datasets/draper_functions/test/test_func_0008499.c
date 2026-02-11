mime_version(struct rfc2045 *p, struct rfc822t *header)
{
char	*vers=paste_tokens(header, 2, header->ntokens-2);

	if (!vers)	return;

	if (p->mime_version)	free(p->mime_version);
	p->mime_version=vers;
}
