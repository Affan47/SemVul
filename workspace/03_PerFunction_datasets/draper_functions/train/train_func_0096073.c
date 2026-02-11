list_msg_mime_multipart(struct rfc2045 *rfc, FILE *fp)
{
	struct rfc2045 *q;
	int first=1;
	int rc;

	for (q=rfc->firstpart; q; q=q->next)
	{
		if (q->isdummy) continue;

		if (!first)
			printf("\n    ------------------------------\n\n");
		first=0;

		rc=list_msg_mime(q, fp);
		if (rc)
			return (rc);
	}
	return (0);
}
